#include "ft_nm.h"

void	print_err_mess(unsigned int mode, char *str, int fd)
{
	ft_dprintf(2, "ft_nm: Warning: \'%s\': is a ", str);
	switch (mode & S_IFMT)
	{
		case S_IFSOCK: ft_dprintf(2, "socket\n"); break ;
		
		case S_IFLNK: ft_dprintf(2, "symbolic link\n"); break ;
		
		case S_IFBLK: ft_dprintf(2, "bloc device\n"); break ;
		
		case S_IFDIR: ft_dprintf(2, "directory\n"); break ;

		case S_IFCHR: ft_dprintf(2, "character device\n"); break ;

		case S_IFIFO: ft_dprintf(2, "FIFO\n"); break ;

		default: ft_dprintf(2, "unknown\n"); break;
	}
	close(fd);
}

static bool	alloc_mem(void **addr, char *file_name, size_t lenght, int fd)
{
	off_t	pa_offset = 0 & ~(sysconf(_SC_PAGE_SIZE) - 1);

	(*addr) = mmap(NULL, lenght - pa_offset, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, pa_offset);
	close(fd);
	if ((*addr) == MAP_FAILED)
	{
		ft_dprintf(2, "ft_nm: \'%s\': Error: mmap failed\n", file_name);
		return false;
	}
	return true;
}

static void	extract_and_print_file(char *file_name, size_t lenght, uint8_t opts, int fd, int num_files)
{
	t_data_32	data_32 = {.opts = opts, .big_endian = false, .addr = NULL, .ehdr = NULL, .shdr = NULL, .shstrtab = NULL, .symtab = NULL, .strtab = NULL, .syms = NULL};
	t_data_64	data_64 = {.opts = opts, .big_endian = false, .addr = NULL, .ehdr = NULL, .shdr = NULL, .shstrtab = NULL, .symtab = NULL, .strtab = NULL, .syms = NULL};
	void	*addr = NULL;

	if (!alloc_mem(&addr, file_name, lenght, fd))
		return ;
	if (!check_elf_header(addr, file_name, lenght, &data_32, &data_64))
		return ;
	
	if (num_files > 1)
			ft_dprintf(1, "\n%s:\n", file_name);

	if (data_32.ehdr)
		extract_nm_32(&data_32, file_name);
	if (data_64.ehdr)
		extract_nm_64(&data_64, file_name);
	if (munmap(addr, lenght))
		ft_dprintf(2, "ft_nm: \'%s\': Error: munmap failed\n", file_name);
}

static void	exec_nm(uint8_t opts, char **files, int num_files)
{
	if (!ft_strcmp(files[0], "a.out"))
	{
		struct stat st;
		int fd = open(files[0], 0);	
		if (fd < 0)
		{
			ft_dprintf(2, "ft_nm: \'%s\': No such file\n", files[0]);
			return ;
		}
		fstat(fd, &st);
		if (S_ISREG(st.st_mode))
			extract_and_print_file(files[0], st.st_size, opts, fd, 1);
		else
			print_err_mess(st.st_mode, files[0], fd);
		return ;
	}

	for (size_t i = 1; files[i] ; i++)
	{
		if (files[i][0] == '-' && ft_strlen(files[i]) > 1)
			continue ;
		struct stat st;
		int fd = open(files[i], 0);	
		if (fd < 0)
		{
			ft_dprintf(2, "ft_nm: \'%s\': No such file\n", files[i]);
			continue ;
		}
		fstat(fd, &st);
		if (S_ISREG(st.st_mode))
			extract_and_print_file(files[i], st.st_size, opts, fd, num_files);
		else
			print_err_mess(st.st_mode, files[i], fd);	
	}
}

int main(int ac, char **av)
{
	(void)ac;
	uint8_t options = 0;
	int	num_files = 0;

	if (!parse_input(&options, av, &num_files))
		return 1;

	exec_nm(options, av, num_files);
	return 0;
}