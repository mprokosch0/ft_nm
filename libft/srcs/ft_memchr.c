/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:19:19 by mprokosc          #+#    #+#             */
/*   Updated: 2024/11/18 12:06:21 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*f;
	unsigned char	uc;

	uc = (unsigned char)c;
	f = (unsigned char *)s;
	while (n--)
	{
		if (*f == uc)
			return ((void *)f);
		f++;
	}
	return (NULL);
}
