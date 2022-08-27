/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:47:16 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/19 15:22:32 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*to;
	const char	*from;
	size_t		i;

	to = dest;
	from = src;
	i = 0;
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	return (to);
}
