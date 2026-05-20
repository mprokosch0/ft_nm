/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:02:32 by mprokosc          #+#    #+#             */
/*   Updated: 2026/05/16 17:06:40 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hex(char c, va_list args, int *len, int fd)
{
	int	nb;

	nb = (int)va_arg(args, int);
	if (c == 'x')
		convert_hex(0, nb, len, fd);
	if (c == 'X')
		convert_hex(1, nb, len, fd);
}
