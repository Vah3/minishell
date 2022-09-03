/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:16:58 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/19 15:22:10 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*st1;
	const char	*st2;
	size_t		index;

	st1 = (const char *)s1;
	st2 = (const char *)s2;
	index = 0;
	while (index < n)
	{
		if (st1[index] != st2[index])
			return ((unsigned char )st1[index] - (unsigned char )st2[index]);
		index++;
	}
	return (0);
}
