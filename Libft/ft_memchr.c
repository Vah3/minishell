/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:31:01 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/18 21:45:12 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		index;
	const char	*scan;

	scan = (const char *) s;
	index = 0;
	while (index < n)
	{
		if (scan[index] == (char) c)
			return ((char *)scan + index);
		index ++;
	}
	return (0);
}
