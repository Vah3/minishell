/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:39:30 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/20 00:22:44 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	index;
	size_t	retvalue;

	i = 0;
	retvalue = 0;
	index = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	while (src[retvalue] != '\0')
		retvalue++;
	retvalue = retvalue + i;
	index = i;
	while (src[i - index] && (i + 1 < dstsize))
	{
		dst[i] = src[i - index];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (retvalue);
}
