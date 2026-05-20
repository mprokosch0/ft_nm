/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:01:52 by mprokosc          #+#    #+#             */
/*   Updated: 2026/05/16 17:07:11 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	convert_hex(int maj, unsigned int nb, int *len, int fd)
{
	char			*set1;
	char			*set2;
	unsigned long	nbr;

	nbr = nb;
	set2 = "0123456789ABCDEF";
	set1 = "0123456789abcdef";
	if (nbr >= 16)
		convert_hex(maj, nbr / 16, len, fd);
	if (maj)
		ft_putchar_fd_printf(set2[nbr % 16], fd, len);
	else
		ft_putchar_fd_printf(set1[nbr % 16], fd, len);
}
