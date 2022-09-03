/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:53:10 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/03 15:34:55 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1 && s2 && index < n)
	{
		if (s1[index] > s2[index])
			return ((unsigned char )s1[index] - (unsigned char )s2[index]);
		else if (s1[index] < s2[index])
			return ((unsigned char )s1[index] - (unsigned char )s2[index]);
		index++;
	}
	return (0);
}
