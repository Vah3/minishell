/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:52:20 by vagevorg          #+#    #+#             */
/*   Updated: 2022/03/23 10:24:13 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*strf;

	i = 0;
	while (s[i] != '\0')
		i++;
	strf = malloc((i + 1) * sizeof(char));
	if (!strf || !s)
		return (0);
	strf[i] = '\0';
	while (i > 0)
	{
		i--;
		strf[i] = f(i, s[i]);
	}
	return (strf);
}
