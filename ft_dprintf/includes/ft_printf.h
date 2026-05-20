/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:20:50 by mprokosc          #+#    #+#             */
/*   Updated: 2026/05/16 17:06:33 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_dprintf(int fd, const char *s, ...);
void	ft_putnbr_fd_printf(int n, int fd, int *len);
void	ft_putchar_fd_printf(char c, int fd, int *len);
size_t	ft_strlen(char const *str);
void	ft_char(va_list args, int *len, int fd);
void	ft_str(va_list args, int *len, int fd);
void	ft_ptr(va_list args, int *len, int fd);
void	ft_putstr_fd_printf(char *s, int fd, int *len);
void	ft_putnbr_unsigned_fd(unsigned int n, int fd, int *len);
void	convert_hex(int maj, unsigned int nb, int *len, int fd);
void	ft_hex(char c, va_list args, int *len, int fd);

#endif
