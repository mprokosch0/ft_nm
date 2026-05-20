#include "ft_nm.h"

static Elf32_Shdr  *get_shdr_32_bits(t_data_32 *data, char *name)
{
    int         idx = 0;
	char        *names = (char *)(data->addr + data->shstrtab->sh_offset);

	while (idx < data->ehdr->e_shnum)
	{
		if (ft_strcmp(names + data->shdr[idx].sh_name, name) == 0)
			return (&data->shdr[idx]);
		idx++;
	}
    return (NULL);
}

static char bind_conv(Elf32_Sym sym, t_data_32 *data,char c)
{
	if (ELF32_ST_BIND(sym.st_info) == STB_WEAK)
	{
		if (ELF32_ST_TYPE(sym.st_info) == STT_OBJECT)
			c = (sym.st_shndx == SHN_UNDEF) ? 'v' : 'V';
		else
			c = (sym.st_shndx == SHN_UNDEF) ? 'w' : 'W';
	}

	if (ELF32_ST_TYPE(sym.st_info) == STT_GNU_IFUNC)
		c = 'i';

	if (c == 'N')
	{
		char *name = data->addr + data->shstrtab->sh_offset + data->shdr[sym.st_shndx].sh_name;
		if (ELF32_ST_TYPE(sym.st_info) == STT_FILE || !ft_strncmp(name, ".debug", 6)
			|| !ft_strncmp(name, ".zdebug", 7))
			;
		else
			c += 32;
	}
	else if (c != '?' && ELF32_ST_BIND(sym.st_info) == STB_LOCAL)
		c += 32;
	return c;
}

static char get_symbol_32(t_data_32 *data, Elf32_Sym sym)
{
	char c = '?';

	if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE) // reserved value crash if we check shrds[sym.st_shndx] here
		c = 'u';
	else if (sym.st_shndx == SHN_ABS) // reserved value crash if we check shrds[sym.st_shndx] here
		c = bind_conv(sym, data,'A');
	else if (sym.st_shndx == SHN_UNDEF) // reserved value crash if we check shrds[sym.st_shndx] here
		c = (ELF32_ST_BIND(sym.st_info) == STB_WEAK) ? 'w' : 'U';
	else if (sym.st_shndx == SHN_COMMON)
		c = bind_conv(sym, data, 'C');

	if (c != '?')
	{
		if (IS_OPT_g(data->opts) && ELF32_ST_BIND(sym.st_info) != STB_GLOBAL && ELF32_ST_BIND(sym.st_info) != STB_WEAK)
			c = ' ';
		else if (IS_OPT_u(data->opts) && !(sym.st_shndx == SHN_UNDEF))
			c = ' ';	
		return c;
	}

	Elf32_Shdr section = data->shdr[sym.st_shndx];

	if ((section.sh_type == SHT_NOBITS && section.sh_flags == (SHF_ALLOC | SHF_WRITE))
		|| (section.sh_type == SHT_NOBITS && section.sh_flags == (SHF_ALLOC | SHF_WRITE | SHF_TLS)))
		c = 'B';
	else if ((section.sh_type == SHT_PROGBITS && section.sh_flags == (SHF_ALLOC | SHF_WRITE))
			|| (section.sh_type == SHT_PROGBITS && section.sh_flags == (SHF_ALLOC | SHF_WRITE | SHF_TLS))
			|| section.sh_type == SHT_PREINIT_ARRAY || section.sh_type == SHT_INIT_ARRAY || section.sh_type == SHT_FINI_ARRAY
			|| section.sh_type == SHT_DYNAMIC)
		c = 'D';
	else if ((section.sh_type == SHT_PROGBITS || section.sh_type == SHT_STRTAB || section.sh_type == SHT_DYNSYM
				|| section.sh_type == SHT_GNU_HASH || section.sh_type == SHT_GNU_versym || section.sh_type == SHT_GNU_verneed)
				&& section.sh_flags == SHF_ALLOC)
		c = 'R';
	else if (section.sh_type == SHT_PROGBITS && section.sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (section.sh_type == SHT_NOTE || section.sh_type == SHT_RELA || section.sh_type == SHT_REL)
		c = 'R';
	else if (section.sh_flags & SHF_MIPS_GPREL)
	{
		if (section.sh_type == SHT_NOBITS)
			c = 'S';
		else
			c = 'G';
	}
	else if (IS_OPT_a(data->opts) && ELF32_ST_TYPE(sym.st_info) == STT_FILE)
		c = 'a';
	else if (!(section.sh_flags & SHF_ALLOC))
		c = 'N';
	
	c = bind_conv(sym, data, c);

	if (IS_OPT_g(data->opts) && ELF32_ST_BIND(sym.st_info) != STB_GLOBAL && ELF32_ST_BIND(sym.st_info) != STB_WEAK)
			c = ' ';
	else if (IS_OPT_u(data->opts) && !(sym.st_shndx == SHN_UNDEF))
		c = ' ';
	
	return c;
}

static void	swap_syms_32(Elf32_Sym *s1, Elf32_Sym *s2)
{
	Elf32_Sym tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort_symbols_32(t_data_32 *data)
{
	size_t count = data->symtab->sh_size / sizeof(Elf32_Sym);

	for (size_t i = 0; i < count; i++)
	{
		for (size_t j = 0; j < count - 1; j++)
		{				
			String_view sv1 = sv_create((char *)(data->addr + data->strtab->sh_offset + data->syms[j].st_name));
			String_view sv2 = sv_create((char *)(data->addr + data->strtab->sh_offset + data->syms[j + 1].st_name));
			if (IS_OPT_a(data->opts) && ELF32_ST_TYPE(data->syms[j].st_info) == STT_SECTION && data->syms[j].st_shndx < data->ehdr->e_shnum)
			{
				Elf32_Shdr *sec = &data->shdr[data->syms[j].st_shndx];
				sv1 = sv_create((char *)(data->addr + data->shstrtab->sh_offset + sec->sh_name));
			}
			if (IS_OPT_a(data->opts) && ELF32_ST_TYPE(data->syms[j + 1].st_info) == STT_SECTION && data->syms[j + 1].st_shndx < data->ehdr->e_shnum)
			{
				Elf32_Shdr *sec = &data->shdr[data->syms[j + 1].st_shndx];
				sv2 = sv_create((char *)(data->addr + data->shstrtab->sh_offset + sec->sh_name));
			}
			int val = sv_strcmp(&sv1, &sv2);
			if (val > 0)
				swap_syms_32(&data->syms[j], &data->syms[j + 1]);
		}
	}
}

void	reverse_symbols_32(t_data_32 *data)
{
	size_t count = data->symtab->sh_size / sizeof(Elf32_Sym);

	for (size_t i = 0; i < count / 2; i++)
		swap_syms_32(&data->syms[i], &data->syms[count - 1 - i]);

	for (size_t i = 0; i < count - 1; i++)
	{
		char *name1 = (char *)(data->addr + data->strtab->sh_offset + data->syms[i].st_name);
		char *name2 = (char *)(data->addr + data->strtab->sh_offset + data->syms[i + 1].st_name);
		if (IS_OPT_a(data->opts) && ELF32_ST_TYPE(data->syms[i].st_info) == STT_SECTION && data->syms[i].st_shndx < data->ehdr->e_shnum)
		{
			Elf32_Shdr *sec = &data->shdr[data->syms[i].st_shndx];
			name1 = (char *)(data->addr + data->shstrtab->sh_offset + sec->sh_name);
		}
		if (IS_OPT_a(data->opts) && ELF32_ST_TYPE(data->syms[i + 1].st_info) == STT_SECTION && data->syms[i].st_shndx < data->ehdr->e_shnum)
		{
			Elf32_Shdr *sec = &data->shdr[data->syms[i + 1].st_shndx];
			name2 = (char *)(data->addr + data->shstrtab->sh_offset + sec->sh_name);
		}
	
		size_t num = 0;

		while (!ft_strcmp(name1, name2) && i + 1 + num < count)
		{	
			name1 = (char *)(data->addr + data->strtab->sh_offset + data->syms[i + num].st_name);
			name2 = (char *)(data->addr + data->strtab->sh_offset + data->syms[i + 1 + num].st_name);
			num++;
		}

		for (size_t j = 0; j < num / 2; j++)
			swap_syms_32(&data->syms[i + j], &data->syms[i + num - 1 - j]);
		if (num > 1)
			num--;
		i += num;
	}
}

void	extract_nm_32(t_data_32 *data, char *file_name)
{
	data->shdr = (Elf32_Shdr *)(data->addr + data->ehdr->e_shoff);
	if (data->big_endian)
	{
		int i = 0;
		while (i < data->ehdr->e_shnum)
		{
			reverse_shdr_32(&data->shdr[i]);
			i++;
		}
	}
	data->shstrtab = &data->shdr[data->ehdr->e_shstrndx];
	data->symtab = get_shdr_32_bits(data, ".symtab");
	if (!data->symtab || data->symtab->sh_size == 0 || data->symtab->sh_entsize == 0)
	{
		ft_dprintf(2, "ft_nm: %s: no symbols\n", file_name);
		return ;
	}
	data->strtab = get_shdr_32_bits(data, ".strtab");
	data->syms = (Elf32_Sym *)(data->addr + data->symtab->sh_offset);

	if (data->big_endian)
		reverse_sym_32(data->symtab, data->syms);

	if (!IS_OPT_p(data->opts))
		sort_symbols_32(data);

	if (!IS_OPT_p(data->opts) && IS_OPT_r(data->opts))
		reverse_symbols_32(data);
	
	int     count = data->symtab->sh_size / sizeof(Elf32_Sym);
	int     i = -1;
	while (++i < count)
	{
		char c = get_symbol_32(data, data->syms[i]);
		char *name = (char *)(data->addr + data->strtab->sh_offset + data->syms[i].st_name);
		uint32_t val = data->syms[i].st_value;

		if (((c == 'a') && !IS_OPT_a(data->opts)) || c == ' ' || !name)
			continue ;
		if (!ft_strcmp(name, "") && ELF32_ST_TYPE(data->syms[i].st_info) != STT_FILE)
		{
			if (IS_OPT_a(data->opts) && ELF32_ST_TYPE(data->syms[i].st_info) == STT_SECTION && data->syms[i].st_shndx < data->ehdr->e_shnum)
			{
				Elf32_Shdr *sec = &data->shdr[data->syms[i].st_shndx];
				name = (char *)(data->addr + data->shstrtab->sh_offset + sec->sh_name);
			}
			else
				continue;
		}
	
		if (data->syms[i].st_shndx != SHN_UNDEF)
			print_hex_32(val);
		else
			ft_dprintf(1, "         ");
		ft_dprintf(1, "%c %s\n", c, name);
	}
}
