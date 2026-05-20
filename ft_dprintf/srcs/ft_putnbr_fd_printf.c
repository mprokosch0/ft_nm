/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:49:49 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/05 16:28:44 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_fd_printf(int n, int fd, int *len)
{
	int	a;

	a = 0;
	if (n == -2147483648)
	{
		ft_putstr_fd_printf("-2147483648", fd, len);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd_printf('-', fd, len);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd_printf(n / 10, fd, len);
	a = (n % 10) + '0';
	ft_putchar_fd_printf(a, fd, len);
}
