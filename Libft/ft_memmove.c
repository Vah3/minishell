/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:21:44 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/19 19:02:23 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*to;
	char	from[1000];
	size_t	i;
	char	*fr;

	to = dst;
	i = 0;
	fr = (char *)src;
	while (i < len)
	{
		from[i] = fr[i];
		i++;
	}
	from[i] = '\0';
	i = 0;
	while (i < len)
	{
		to[i] = from[i];
		i++;
	}
	return (to);
}
