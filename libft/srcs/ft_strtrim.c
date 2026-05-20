/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:21:52 by mprokosc          #+#    #+#             */
/*   Updated: 2024/11/18 12:17:14 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char const c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	str_start(char const *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	return (i);
}

static int	str_end(char const *s1, char const *set)
{
	unsigned int	i;

	i = ft_strlen(s1) - 1;
	while (i > 0 && is_in_set(s1[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	len;
	char			*dest;

	if (!*s1)
	{
		dest = malloc(sizeof(char));
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	start = str_start(s1, set);
	end = str_end(s1, set);
	len = end - start + 1;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1 + start, len + 1);
	return (dest);
}
