/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:44:56 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/27 19:43:00 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

char	*ft_print(const char *k, int t, int z)
{
	char	*ban;
	int		g;

	g = 0;
	ban = malloc(t - z + 2);
	if (!ban)
		return (0);
	while (z <= t)
	{
		ban[g] = k[z];
		g++;
		z++;
	}
	ban[g] = '\0';
	return (ban);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		a;
	int		c;

	a = 0;
	i = 0;
	while (set[i] != '\0')
	{	
		if (s1[a] == set[i] && s1[a++])
			i = 0;
		else
			i++;
	}
	c = a;
	i = 0;
	a = (int)ft_strlen(s1) - 1;
	while (set[i] != '\0' && a >= c)
	{
		if (s1[a] == set[i] && s1[a--])
			i = 0;
		else
			i++;
	}
	return (ft_print(s1, a, c));
}
