/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freee.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:52:48 by mprokosc          #+#    #+#             */
/*   Updated: 2025/05/06 14:10:00 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freee(void **ptr, size_t size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		if (ptr[i++])
			free(ptr[i - 1]);
	}
	if (ptr)
		free(ptr);
}
