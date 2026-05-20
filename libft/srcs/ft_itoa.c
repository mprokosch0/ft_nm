/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:43:18 by mprokosc          #+#    #+#             */
/*   Updated: 2024/11/18 12:03:25 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_nb(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	if (n == 0)
		return (1);
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	unsigned int	i;
	unsigned int	num;
	char			*dest;

	i = len_nb(n);
	dest = (char *)malloc(sizeof(char) * (1 + i));
	if (!dest)
		return (NULL);
	dest[i] = '\0';
	i--;
	if (n < 0)
	{
		dest[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (num >= 10)
	{
		dest[i] = ('0' + num % 10);
		num /= 10;
		i--;
	}
	dest[i] = ('0' + num);
	return (dest);
}
