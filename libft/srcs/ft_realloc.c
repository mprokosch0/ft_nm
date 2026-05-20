/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:51:59 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/26 16:23:32 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	void	*new;

	if (!ptr)
	{
		ptr = malloc(size);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (size <= 0)
		return (free(ptr), NULL);
	if (size > old_size)
	{
		new = malloc(size);
		ft_memcpy(new, ptr, old_size);
	}
	else
	{
		new = malloc(size);
		ft_memcpy(new, ptr, size);
	}
	free(ptr);
	return (new);
}
