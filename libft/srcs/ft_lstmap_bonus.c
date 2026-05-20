/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:27:02 by mprokosc          #+#    #+#             */
/*   Updated: 2024/11/18 11:08:11 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elmt;
	void	*new_content;

	new_lst = NULL;
	while (lst)
	{
		new_content = (*f)(lst->content);
		new_elmt = ft_lstnew(new_content);
		if (!new_elmt && del)
		{
			ft_lstclear(&new_elmt, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_elmt);
		lst = lst->next;
	}
	return (new_lst);
}
