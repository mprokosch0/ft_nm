/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:14:24 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/05 16:26:21 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_str(va_list args, int *len, int fd)
{
	char	*d;

	d = (char *)va_arg(args, char *);
	if (!d)
	{
		ft_putstr_fd_printf("(null)", fd, len);
		return ;
	}
	ft_putstr_fd_printf(d, fd, len);
}
