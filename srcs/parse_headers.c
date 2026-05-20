#include "ft_nm.h"

static void	fill_32_bits_Elf_header_high_endian(String_view *sv, Elf32_Ehdr **header)
{
	(*header) = (Elf32_Ehdr *)sv->str;

	ui16_byte_swap(&(*header)->e_type);
	ui16_byte_swap(&(*header)->e_machine);
	ui32_byte_swap(&(*header)->e_version);
	ui32_byte_swap(&(*header)->e_entry);
	ui32_byte_swap(&(*header)->e_phoff);
	ui32_byte_swap(&(*header)->e_shoff);
	ui32_byte_swap(&(*header)->e_flags);
	ui16_byte_swap(&(*header)->e_ehsize);
	ui16_byte_swap(&(*header)->e_phentsize);
	ui16_byte_swap(&(*header)->e_phnum);
	ui16_byte_swap(&(*header)->e_shentsize);
	ui16_byte_swap(&(*header)->e_shnum);
	ui16_byte_swap(&(*header)->e_shstrndx);
}

static void	fill_64_bits_Elf_header_high_endian(String_view *sv, Elf64_Ehdr **header)
{
	(*header) = (Elf64_Ehdr *)sv->str;

	ui16_byte_swap(&(*header)->e_type);
	ui16_byte_swap(&(*header)->e_machine);
	ui32_byte_swap(&(*header)->e_version);
	ui64_byte_swap(&(*header)->e_entry);
	ui64_byte_swap(&(*header)->e_phoff);
	ui64_byte_swap(&(*header)->e_shoff);
	ui32_byte_swap(&(*header)->e_flags);
	ui16_byte_swap(&(*header)->e_ehsize);
	ui16_byte_swap(&(*header)->e_phentsize);
	ui16_byte_swap(&(*header)->e_phnum);
	ui16_byte_swap(&(*header)->e_shentsize);
	ui16_byte_swap(&(*header)->e_shnum);
	ui16_byte_swap(&(*header)->e_shstrndx);
}


void print_type(uint16_t val)
{
	switch (val)
	{
		case EM_NONE:
			ft_dprintf(1, "UNKNOWN\n");
			break;
		case EM_M32:
			ft_dprintf(1, "AT&T WE 32100\n");
			break;
		case EM_SPARC:
			ft_dprintf(1, "Sun Microsystems SPARC\n");
			break;
		case EM_386:
			ft_dprintf(1, "Intel 80386\n");
			break;
		case EM_68K:
			ft_dprintf(1, "Motorola 68000\n");
			break;
		case EM_88K:
			ft_dprintf(1, "Motorola 88000\n");
			break;
		case EM_860:
			ft_dprintf(1, "Intel 80860\n");
			break;
		case EM_MIPS:
			ft_dprintf(1, "MIPS RS3000 (big-endian only)\n");
			break;
		case EM_PARISC:
			ft_dprintf(1, "HP/PA\n");
			break;
		case EM_SPARC32PLUS:
			ft_dprintf(1, "SPARC with enhanced instruction set\n");
			break;
		case EM_PPC:
			ft_dprintf(1, "PowerPC\n");
			break;
		case EM_PPC64:
			ft_dprintf(1, "PowerPC 64-bit\n");
			break;
		case EM_S390:
			ft_dprintf(1, "IBM S/390\n");
			break;
		case EM_ARM:
			ft_dprintf(1, "Advanced RISC Machines\n");
			break;
		case EM_SH:
			ft_dprintf(1, "Renesas SuperH\n");
			break;
		case EM_SPARCV9:
			ft_dprintf(1, "SPARC v9 64-bit\n");
			break;
		case EM_IA_64:
			ft_dprintf(1, "Intel Itanium\n");
			break;
		case EM_X86_64:
			ft_dprintf(1, "AMD x86-64\n");
			break;
		case EM_VAX:
			ft_dprintf(1, "DEC Vax\n");
			break;		
		default:
			ft_dprintf(1, "UNKNOWN 2\n");
			break;
	}
}

static int	fill_data_32(void *addr, size_t length, t_data_32 *data_32, String_view sv)
{
	data_32->addr = addr;
	if (sv.str[EI_DATA] == ELFDATA2LSB)
		data_32->ehdr = (Elf32_Ehdr *)sv.str;
	else if (sv.str[EI_DATA] == ELFDATA2MSB)
	{
		fill_32_bits_Elf_header_high_endian(&sv, &data_32->ehdr);
		data_32->big_endian = true;
	}
	else
		return -1;
	if (data_32->ehdr->e_machine != EM_386 && data_32->ehdr->e_machine != EM_PPC)
	{
		if (data_32->ehdr->e_machine == EM_X86_64 || data_32->ehdr->e_machine != EM_PPC64)
			return 1;
		return -1;
	}
	if (data_32->ehdr->e_shoff >= length || data_32->ehdr->e_phoff >= length)
		return -1;
	return 0;
}

static int	fill_data_64(void *addr, size_t length, t_data_64 *data_64, String_view sv)
{
	data_64->addr = addr;
	if (sv.str[EI_DATA] == ELFDATA2LSB)
		data_64->ehdr = (Elf64_Ehdr *)sv.str;
	else if (sv.str[EI_DATA] == ELFDATA2MSB)
	{
		fill_64_bits_Elf_header_high_endian(&sv, &data_64->ehdr);
		data_64->big_endian = true;
	}
	else
		return -1;
	if (data_64->ehdr->e_machine != EM_X86_64 && data_64->ehdr->e_machine != EM_PPC64)
	{
		if (data_64->ehdr->e_machine == EM_386 || data_64->ehdr->e_machine == EM_PPC)
			return 1;
		return -1;
	}
	if (data_64->ehdr->e_shoff >= length || data_64->ehdr->e_phoff >= length)
		return -1;
	return 0;
}

bool	check_elf_header(void *addr, const char *file_name, size_t lenght, t_data_32 *data_32, t_data_64 *data_64)
{
	String_view sv = sv_create_len((char *)(addr), HEADER_64_LENGTH);

	if (sv_find(&sv, ELFMAG) == NPOS || sv.str[EI_VERSION] == EV_NONE)
		return unmap(addr, lenght, file_name);

	if (sv.str[EI_CLASS] == ELFCLASS32)
	{
		int val = fill_data_32(addr, lenght, data_32, sv);
		if (val < 0)
			return unmap(addr, lenght, file_name);
		else if (val > 0)
		{
			data_32->ehdr = NULL;
			if (fill_data_64(addr, lenght, data_64, sv))
				return unmap(addr, lenght, file_name);
		}
	}
	else if (sv.str[EI_CLASS] == ELFCLASS64)
	{
		int val = fill_data_64(addr, lenght, data_64, sv);
		if (val < 0)
			return unmap(addr, lenght, file_name);
		else if (val > 0)
		{
			data_64->ehdr = NULL;
			if (fill_data_32(addr, lenght, data_32, sv))
				return unmap(addr, lenght, file_name);
		}
	}
	else
		return unmap(addr, lenght, file_name);

	return true;
}

void	reverse_shdr_32(Elf32_Shdr *shdr)
{
	ui32_byte_swap(&shdr->sh_name);
	ui32_byte_swap(&shdr->sh_type);
	ui32_byte_swap(&shdr->sh_flags);
	ui32_byte_swap(&shdr->sh_addr);
	ui32_byte_swap(&shdr->sh_offset);
	ui32_byte_swap(&shdr->sh_size);
	ui32_byte_swap(&shdr->sh_link);
	ui32_byte_swap(&shdr->sh_info);
	ui32_byte_swap(&shdr->sh_addralign);
	ui32_byte_swap(&shdr->sh_entsize);
}

void	reverse_shdr_64(Elf64_Shdr *shdr)
{
	ui32_byte_swap(&shdr->sh_name);
	ui32_byte_swap(&shdr->sh_type);
	ui64_byte_swap(&shdr->sh_flags);
	ui64_byte_swap(&shdr->sh_addr);
	ui64_byte_swap(&shdr->sh_offset);
	ui64_byte_swap(&shdr->sh_size);
	ui32_byte_swap(&shdr->sh_link);
	ui32_byte_swap(&shdr->sh_info);
	ui64_byte_swap(&shdr->sh_addralign);
	ui64_byte_swap(&shdr->sh_entsize);
}

void	reverse_sym_32(Elf32_Shdr *symtab, Elf32_Sym *syms)
{
	int count = symtab->sh_size / sizeof(Elf32_Sym);

	int i = 0;
	while (i < count)
	{
		ui32_byte_swap(&syms[i].st_name);
		ui32_byte_swap(&syms[i].st_value);
		ui32_byte_swap(&syms[i].st_size);
		ui16_byte_swap(&syms[i].st_shndx);
		i++;
	}
}

void	reverse_sym_64(Elf64_Shdr *symtab, Elf64_Sym *syms)
{
	int count = symtab->sh_size / sizeof(Elf64_Sym);

	int i = 0;
	while (i < count)
	{
		ui32_byte_swap(&syms[i].st_name);
		ui16_byte_swap(&syms[i].st_shndx);
		ui64_byte_swap(&syms[i].st_value);
		ui64_byte_swap(&syms[i].st_size);
		i++;
	}
}