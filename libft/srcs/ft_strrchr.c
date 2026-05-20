/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:07:14 by mprokosc          #+#    #+#             */
/*   Updated: 2024/11/18 12:16:38 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	uc;

	uc = (unsigned char)c;
	i = ft_strlen(s);
	if (s[i] == uc)
		return ((char *)&s[i]);
	while (i--)
	{
		if (s[i] == uc)
			return ((char *)&s[i]);
	}
	return (NULL);
}
