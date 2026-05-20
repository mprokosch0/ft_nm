#include "ft_nm.h"

static void	print_help_mess(char *opt)
{
	if (ft_strlen(opt) == 1)
		ft_dprintf(2, "ft_nm: invalid option -- \'%c\'\n", opt[0]);
	else
		ft_dprintf(2, "ft_nm: unrecognise option -- \'%s\'\n", opt);
	ft_dprintf(2, "Usage: ft_nm [option(s)] [file(s)]\n");
	ft_dprintf(2, " List symbols in [file(s)] (a.out by default).\n");
	ft_dprintf(2, " The options are:\n");
	ft_dprintf(2, "  -a, --debug-syms\tDisplay debugger-only symbols\n");
	ft_dprintf(2, "  -g, --extern-only\tDisplay only external symbols\n");
	ft_dprintf(2, "  -p, --no-sort\t\tDo not sort the symbols\n");
	ft_dprintf(2, "  -r, --reverse-sort\tReverse the sense of the sort\n");
	ft_dprintf(2, "  -u, --undefined-only\tDisplay only undefined symbols\n");
}

static int single_char_opt(uint8_t *options, char *str)
{
	for (size_t j = 1; str[j]; j++)
	{
		switch (str[j])
		{
			case 'a':
				(*options) |= 0b1;
				break ;
			
			case 'g':
				(*options) |= 0b10;
				break ;
				
			case 'p':
				(*options) |= 0b100;
				break ;

			case 'r':
				(*options) |= 0b1000;
				break ;

			case 'u':
				(*options) |= 0b10000;
				break ;
				
			default:
				print_help_mess(&str[j]);
				return false;
		}
	}
	return true;
}

static bool str_opt(uint8_t *options, char *str)
{
	if (!ft_strcmp(str, "debug-syms"))
		(*options) |= 0b1;
	else if (!ft_strcmp(str, "extern-only"))
		(*options) |= 0b10;
	else if (!ft_strcmp(str, "no-sort"))
		(*options) |= 0b100;
	else if (!ft_strcmp(str, "reverse-sort"))
		(*options) |= 0b1000;
	else if (!ft_strcmp(str, "undefined-only"))
		(*options) |= 0b10000;
	else
	{
		print_help_mess(str);
		return false;
	}
	return true;
}

static bool manage_options(uint8_t *options, char **av, int *num_files)
{
	for (size_t i = 1; av[i]; i++)
	{
		if (av[i][0] == '-' && ft_strlen(av[i]) > 1)
		{
			if (av[i][1] == '-')
			{
				if (!str_opt(options, av[i] + 2))
					return false;
			}
			else
				if (!single_char_opt(options, av[i]))
					return false;	
		}
		else
			(*num_files)++;
	}
	return true;
}	

bool parse_input(uint8_t *options, char **av, int *num_files)
{
	if (!manage_options(options, av, num_files))
		return false;
	if (!(*num_files))
		ft_strlcpy(av[0], "a.out", 6);
	return true;
}