#include "libft.h"

// create a string_viewer
String_view	sv_create(char *str)
{
	return (String_view){.str = str, .size = ft_strlen(str)};
}

// create a string_viewer with len
String_view	sv_create_len(char *str, size_t len)
{
	size_t len2 = ft_strlen(str);
	if (len > len2)
		return (String_view){.str = str, .size = len2};
	return (String_view){.str = str, .size = len};
}

// cut n chars at the left of the string
void	sv_cut_left(String_view *sv, size_t n)
{
	if (!sv->size)
		return ;
	
	while (n-- && sv->size)
	{
		sv->str++;
		sv->size--;
	}
}

// cut n chars at the right of the string
void	sv_cut_right(String_view *sv, size_t n)
{
	if (!sv->size)
		return ;

	while (n-- && sv->size)
		sv->size--;
}

// trim all the spaces at the left of the string_view
void	sv_trim_left(String_view *sv)
{
	while (sv->size && ft_isspace(sv->str[0]))
		sv_cut_left(sv, 1);
}

// trim all the spaces at the right of the string_view
void	sv_trim_right(String_view *sv)
{
	while (sv->size && ft_isspace(sv->str[sv->size - 1]))
		sv_cut_right(sv, 1);
}

// trim all the spaces at the left and right of the string_view
void	sv_trim(String_view *sv)
{
	sv_trim_left(sv);
	sv_trim_right(sv);
}

// split the string_view with the delim, and return (0) the first part and (1) the left part
String_view	sv_cut_delim(String_view *sv, int delim, int which_part)
{
	size_t i = 0;

	for (i = 0; i < sv->size; i++)
	{
		if (sv->str[i] == delim)
			break ;
	}
	
	if (i == sv->size)
		return *sv;
	
	if (!which_part)
		return (String_view){.str = sv->str, .size = i};
	return (String_view){.str = sv->str + i + 1, .size = sv->size - i};
}

// split the string_view with the pos, and return (0) the first part and (1) the left part
String_view	sv_cut_pos(String_view *sv, size_t pos, int which_part)
{
	if (pos >= sv->size)
		return *sv;
	
	if (!which_part)
		return (String_view){.str = sv->str, .size = pos};
	return (String_view){.str = sv->str + pos, .size = sv->size - pos};
}

// search for a string in the string_view, if the string is found, it returns the pos of the first char, else it returns NPOS
size_t sv_find(String_view *sv, const char *str)
{
	for (size_t i = 0; i < sv->size; i++)
	{
		size_t j = 0;
		while (str[j] && i + j < sv->size && sv->str[i + j] == str[j])
			j++;
		if (j == ft_strlen(str))
			return i;
	}
	return NPOS;
}

int	sv_strcmp(String_view *s1, String_view *s2)
{
	size_t	n;

	if (!s1 || !s2)
		return (-1);
	n = 0;
	while (n < s1->size && n < s2->size && (s1->str[n] == s2->str[n]))
		n++;
	return (s1->str[n] - s2->str[n]);
}

// print the string_view
void	sv_print(String_view sv)
{
	for (size_t i = 0; i < sv.size; i++)
		write(1, &sv.str[i], 1);
}

// print the string_view with new line
void	sv_print_nl(String_view sv)
{
	for (size_t i = 0; i < sv.size; i++)
		write(1, &sv.str[i], 1);
	write(1, "\n", 1);
}