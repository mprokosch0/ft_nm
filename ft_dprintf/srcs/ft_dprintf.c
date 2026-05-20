/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpichon <gpichon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:28:34 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/17 19:18:48 by gpichon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "stdio.h"

int	m_args(char c, va_list args, int *len, int fd)
{
	if (c == 'c')
		ft_char(args, len, fd);
	else if (c == 's')
		ft_str(args, len, fd);
	else if (c == 'p')
		ft_ptr(args, len, fd);
	else if (c == 'd' || c == 'i')
		ft_putnbr_fd_printf((int)va_arg(args, int), fd, len);
	else if (c == 'u')
		ft_putnbr_unsigned_fd((unsigned int)va_arg(args, unsigned int),
			fd, len);
	else if (c == 'X' || c == 'x')
		ft_hex(c, args, len, fd);
	else if (c == '%')
		ft_putchar_fd_printf('%', 1, len);
	return (0);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	args;
	int		len;

	if (!s)
		return (-1);
	len = 0;
	va_start(args, s);
	while (*s)
	{
		while (*s && *s != '%')
		{
			ft_putchar_fd_printf(*s, fd, &len);
			s++;
		}
		if (*s == '%')
		{
			m_args(s[1], args, &len, fd);
			if (s[2])
				s += 2;
			else
				break ;
		}
	}
	va_end(args);
	return (len);
}
