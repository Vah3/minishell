/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:00:43 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/11 18:25:49 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	index;

	index = 0;
	if (!s)
		return (NULL);
	while (s[index])
	{
		if (s[index] == (char )c)
			return ((char *)s + index);
		index++;
	}
	if (c != '\0')
		return (0);
	return ((char *)s + index);
}
