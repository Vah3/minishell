/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:45:38 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/19 21:16:57 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*alloc;
	int		i;

	alloc = malloc(count * size);
	i = count * size;
	if (!alloc)
		return (0);
	while (i > 0)
	{
		i--;
		alloc[i] = '\0';
	}
	return (alloc);
}
