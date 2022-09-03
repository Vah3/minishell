/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:41:06 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/28 15:56:20 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[index] != '\0' && index < len)
	{
		i = 0;
		while (haystack[index + i] == needle[i] && index + i < len)
		{
			if (needle[i + 1] == '\0')
				return ((char *)haystack + index);
			i++;
		}
		index++;
	}
	return (0);
}
