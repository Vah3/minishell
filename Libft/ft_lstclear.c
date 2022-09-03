/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:05:23 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/28 14:14:38 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*buf;

	while ((*lst))
	{
		buf = (*lst)->next;
		del ((*lst)->content);
		free (*lst);
		*lst = buf;
	}
	*lst = NULL;
}
