/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_substr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:47:26 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/11 15:24:49 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim_substr(char **source, int start, int end)
{
	char	*ret_string;
	char	*new_string;
	int		i;

	ret_string = ft_substr(*source, start, end - start);
	new_string = malloc(sizeof(char) * (
				ft_strlen(*source) - (end - start) + 1));
	i = -1;
	while ((*source)[++i] && i < start)
		new_string[i] = (*source)[i];
	while ((*source)[end] && end < (int)ft_strlen(*source))
		new_string[i++] = (*source)[end++];
	new_string[i] = '\0';
	free(*source);
	if (!new_string || !*new_string)
	{
		free (new_string);
		*source = NULL;
	}
	else
		*source = new_string;
	return (ret_string);
}
