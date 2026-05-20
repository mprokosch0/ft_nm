/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:18:35 by mprokosc          #+#    #+#             */
/*   Updated: 2024/11/18 12:14:52 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	destlen;
	size_t	i;
	size_t	srclen;

	i = 0;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (size > 0)
	{
		while (src[i] && destlen + i < size - 1)
		{
			dest[destlen + i] = src[i];
			i ++;
		}
		dest[destlen + i] = '\0';
	}
	if (size <= destlen)
		return (srclen + size);
	else
		return (srclen + destlen);
}
