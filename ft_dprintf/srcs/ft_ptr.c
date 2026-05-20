/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:21:26 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/05 16:26:32 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_ptr(va_list args, int *len, int fd)
{
	void	*d;

	d = (void *)va_arg(args, void *);
	if (!(unsigned long)d)
	{
		ft_putstr_fd_printf("(nil)", fd, len);
		return ;
	}
	ft_putstr_fd_printf("0x", fd, len);
	convert_hex(0, (unsigned long)d, len, fd);
}
