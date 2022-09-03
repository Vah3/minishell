/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:27:55 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/22 15:24:29 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*v;
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	v = (char *) malloc(i + 1);
	if (v == '\0')
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		v[i] = s[i];
		i++;
	}
	v[i] = '\0';
	return (v);
}
