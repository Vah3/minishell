/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:46:49 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/24 15:56:00 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

static void	skipquotes1(char **promt, int *j)
{
	int	i;

	i = *j;
	if (i > 0 && (*promt)[i - 1] && (*promt)[i - 1] == 92)
	{
		(*j)++;
		return ;
	}
	if ((*promt)[i] && (*promt)[i] == 34)
	{
		i++;
		while ((*promt)[i] && (*promt)[i] != 34)
			i++;
		if ((*promt)[i])
			i++;
	}
	if ((*promt)[i] && (*promt)[i] == 39)
	{
		i++;
		while ((*promt)[i] && (*promt)[i] != 39)
			i++;
		if ((*promt)[i])
			i++;
	}
	*j = i;
}

static size_t	ft_count(char const *str, char j)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == j)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != j)
		{		
			if (str[i] == 34 || str[i] == 39)
				skipquotes1((char **)&str, (int *)&i);
			else
			{
				if (str[i])
				i++;
			}
		}
	}
	return (count);
}

void	iterstring(char *s, int *len, char c)
{
	while (s[*len] != c && s[*len])
	{
		if (s[*len] == 34 || s[*len] == 39)
			skipquotes1(&s, len);
		else
			*len += 1;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	start;
	size_t	len;
	size_t	z;

	array = (char **)malloc ((ft_count(s, c) + 1) * sizeof(char *));
	if (!array || !s)
		return (0);
	z = 0;
	start = 0;
	len = 0;
	while (z < ft_count(s, c))
	{
		while (s[start] == c)
			start++;
		len = start;
		iterstring((char *)s, (int *)&len, c);
		array[z] = ft_substr(s, start, (len - start));
		start = len;
		z++;
	}
	array[z] = 0;
	return (array);
}
