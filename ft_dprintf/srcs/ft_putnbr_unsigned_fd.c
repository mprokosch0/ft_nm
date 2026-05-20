/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:49:49 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/05 16:29:53 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_unsigned_fd(unsigned int n, int fd, int *len)
{
	unsigned int	a;

	a = 0;
	if (n >= 10)
		ft_putnbr_unsigned_fd(n / 10, fd, len);
	a = (n % 10) + '0';
	ft_putchar_fd_printf(a, fd, len);
}
