/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:21:38 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/05 16:37:42 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_fd_printf(char *s, int fd, int *len)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd_printf(s[i], fd, len);
		i++;
	}
}
