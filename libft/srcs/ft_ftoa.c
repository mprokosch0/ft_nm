/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:45:58 by mprokosc          #+#    #+#             */
/*   Updated: 2025/07/04 12:14:26 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	powi(int precis)
{
	auto int i = 0, res = 1.0;
	while (i++ < precis)
		res *= 10.0;
	return (res);
}

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

static void	loop(char *dest, unsigned int tab[2], int flag, int precis)
{
	int	count;

	count = 0;
	while (tab[0] >= 10)
	{
		dest[tab[1]--] = ('0' + tab[0] % 10);
		tab[0] /= 10;
		count++;
		if (flag && (int)count == precis && precis > 0)
			dest[tab[1]--] = '.';
	}
	dest[tab[1]--] = ('0' + tab[0]);
}

static char	*fill_zero(float n, int precis, char *dest, int i)
{
	auto int sign = 1;
	auto unsigned int num, count = 0, count2 = 0, tab[2];
	if (n < 0)
	{
		dest[0] = '-';
		sign = -1;
		i++;
		count++;
	}
	num = n * powi(precis) * sign;
	while (!(int)n)
	{
		if (count2 == 1)
			dest[count++] = '.';
		dest[count++] = '0';
		if ((int)count2 == precis)
			return (dest);
		count2++;
		n *= 10;
	}
	if (count2 == 1)
		dest[count] = '.';
	tab[0] = num;
	tab[1] = i;
	return (loop(dest, tab, 0, precis), dest);
}

char	*ft_ftoa(float n, int precis)
{
	char			*dest;
	unsigned int	i;
	unsigned int	num;
	int				sign;

	sign = 1;
	i = len_nb(n) + precis + 1;
	dest = (char *)malloc(sizeof(char) * (1 + i));
	if (!dest)
		return (NULL);
	dest[i--] = '\0';
	if (!(int)n)
		return (fill_zero(n, precis, dest, i));
	if (n < 0)
	{
		dest[0] = '-';
		sign = -1;
	}
	num = n * powi(precis) * sign;
	loop(dest, (unsigned int [2]){num, i}, 1, precis);
	return (dest);
}
