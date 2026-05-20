/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:09:47 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/05 16:26:12 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_char(va_list args, int *len, int fd)
{
	char	c;

	c = (int)va_arg(args, int);
	ft_putchar_fd_printf(c, fd, len);
}
