/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:07:55 by mprokosc          #+#    #+#             */
/*   Updated: 2024/11/18 12:00:53 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int				sign;
	int				val;
	unsigned char	*f;

	val = 0;
	sign = 1;
	f = (unsigned char *)nptr;
	while (*f == 32 || (*f >= 9 && *f <= 13))
		f++;
	if (*f == '+' || *f == '-')
	{
		if (*f == '-')
			sign = -sign;
		f++;
	}
	while (*f >= '0' && *f <= '9')
	{
		val = (val * 10) + *f - '0';
		f++;
	}
	return (val * sign);
}
