/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:55:47 by mprokosc          #+#    #+#             */
/*   Updated: 2024/11/18 12:06:43 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*f1;
	unsigned char	*f2;

	if (!n)
		return (0);
	i = 0;
	f1 = (unsigned char *)s1;
	f2 = (unsigned char *)s2;
	while (i < n - 1 && f1[i] == f2[i])
		i++;
	return (f1[i] - f2[i]);
}
