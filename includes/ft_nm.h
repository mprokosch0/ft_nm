#ifndef FT_NM_H

# define FT_NM_H

# include "libft.h"
# include "ft_printf.h"
# include <stdint.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <elf.h>

# define HEADER_64_LENGTH 64
# define HEADER_32_LENGTH 52

# define IS_OPT_a(val) ((val) & 1)
# define IS_OPT_g(val) ((val) & 2)
# define IS_OPT_p(val) ((val) & 4)
# define IS_OPT_r(val) ((val) & 8)
# define IS_OPT_u(val) ((val) & 16)

typedef struct ft_nm_32
{
	uint8_t		opts;
	bool		big_endian;
	void		*addr;
	Elf32_Ehdr	*ehdr;
	Elf32_Shdr	*shdr;
	Elf32_Shdr	*shstrtab;
	Elf32_Shdr	*symtab;
	Elf32_Shdr	*strtab;
	Elf32_Sym	*syms;
}	t_data_32;

typedef struct ft_nm_64
{
	uint8_t		opts;
	bool		big_endian;
	void		*addr;
	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*shdr;
	Elf64_Shdr	*shstrtab;
	Elf64_Shdr	*symtab;
	Elf64_Shdr	*strtab;
	Elf64_Sym	*syms;
}	t_data_64;

// parse_args.c

bool parse_input(uint8_t *options, char **av, int *num_files);

// parse_headers.c

bool	check_elf_header(void *addr, const char *file_name, size_t lenght, t_data_32 *data_32, t_data_64 *data_64);
void	reverse_shdr_32(Elf32_Shdr *shdr);
void	reverse_shdr_64(Elf64_Shdr *shdr);
void	reverse_sym_32(Elf32_Shdr *symtab, Elf32_Sym *syms);
void	reverse_sym_64(Elf64_Shdr *symtab, Elf64_Sym *syms);

// extract_nm_32

void	extract_nm_32(t_data_32 *data, char *file_name);

// extract_nm_64.c

void	extract_nm_64(t_data_64 *data, char *file_name);

// utils.c

void	ui16_byte_swap(uint16_t *addr);
void	ui32_byte_swap(uint32_t *addr);
void	ui64_byte_swap(uint64_t *addr);
void	print_hex_32(uint32_t nb);
void	print_hex_64(uint64_t nb);
bool	unmap(void *addr, size_t lenght, const char *file_name);

#endif
