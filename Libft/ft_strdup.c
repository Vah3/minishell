/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:27:55 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/01 21:14:26 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*v;
	int		i;
	
	if (!s)
		return (NULL);
	
	i = 0;
	while (s && *s && s[i] != '\0')
		i++;
	v = (char *) malloc(i + 1);
	if (!v)
		return (0);
	i = 0;
	while (s && *s && s[i] != '\0')
	{
		v[i] = s[i];
		i++;
	}
	v[i] = '\0';
	return (v);
}
