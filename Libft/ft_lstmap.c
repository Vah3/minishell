/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:01:36 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/27 20:47:49 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*first_pointer;

	first_pointer = ft_lstnew(f(lst->content));
	if (first_pointer == 0)
		return (0);
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (new == 0)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&first_pointer, new);
		lst = lst->next;
	}
	return (first_pointer);
}
