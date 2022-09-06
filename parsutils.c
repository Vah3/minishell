/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 13:28:35 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/03 16:46:01 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skipquotes(char **promt, int *j)
{
	int	i;

	i = *j;
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
		while ((*promt[i]) && (*promt)[i] != 39)
			i++;
		if ((*promt)[i])
			i++;
	}
	*j = i;
}

int	trimspaces(char **promt, int *k, int *j, char c)
{
	int		i;
	int		range;
	char	*trimed;

	i = *k;
	*j = i;
	range = 1;
	if ((*promt))
	{
		if (*j > 1 && (*promt)[(*j) - 1] && (*promt)[(*j) - 1] == c
			&& (*promt)[(*j) - 2] && (*promt)[(*j) - 2] == c)
			range = 2;
		while ((*promt)[i] && (*promt)[i] == 32)
				i++;
		if (!(*promt)[i])
			return (ft_error("Syntax error\n", 1));
		trimed = ft_trim_substr(promt, (*j) - range, i);
		free(trimed);
		i = *j - range;
		*k = i;
	}
	return (0);
}

void	iffiles(char **promt, int *k, int *j)
{
	int	i;

	i = *k;
	*j = i;
	if ((*promt)[i] && (*promt)[i] == 34 && (*promt)[i++])
	{
		while ((*promt)[i] && ((*promt)[i] != 34) | ((*promt)[i + 1]
				&& (*promt)[i + 1] != 32))
			i++;
		if ((*promt)[i])
			i++;
	}
	else if ((*promt)[i] && (*promt)[i] == 39 && (*promt)[i++])
	{
		while ((*promt)[i] && ((*promt)[i] != 39) | ((*promt)[i + 1]
					&& (*promt)[i + 1] != 32))
			i++;
		if ((*promt[i]))
			i++;
	}
	else
		while ((*promt)[i] && (*promt)[i] != 32)
			i++;
	*k = i;
}

void	duporjoin(char **line, char **promt, int i, int j)
{
	char	*trimed;

	trimed = NULL;
	if (!(*line))
		*line = ft_trim_substr(promt, j, i);
	else
	{
		*line = ft_strjoin(*line, " ");
		trimed = ft_trim_substr(promt, j, i);
		*line = ft_strjoin(*line, trimed);
		free(trimed);
	}
}
