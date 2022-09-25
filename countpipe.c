/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countpipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:07:22 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/25 10:18:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_index_until_pipe(char **promt, int *i)
{
	while ((*promt)[*i] && (*promt)[*i] != '|')
	{
		skipquotes(promt, i);
		if ((*promt)[*i])
			(*i)++;
	}
}

static int	when_promt_ends_with_pipe(char **promt, int i)
{
	char	*newline;

	newline = NULL;
	if (!(*promt)[i])
	{
		while (newline == NULL || ft_strlen(newline) == 0)
			newline = readline(">");
		if (not_found_second_quote(newline))
			return (ft_error("Quote error\n", 1));
		if (only_pipe(newline))
			return (ft_error("There is only pipe\n", 1));
		*promt = ft_strjoin(*promt, " ");
		*promt = ft_strjoin(*promt, newline);
		free(newline);
		newline = NULL;
	}
	return (0);
}

int	check_pipes_count(char **promt, int *count)
{
	int		i;

	*count = 1;
	i = 0;
	while ((*promt)[i])
	{
		skip_index_until_pipe(promt, &i);
		if ((*promt)[i] && (*promt)[i] == '|')
		{
			(*count)++;
			i++;
			while ((*promt)[i] && (*promt)[i] == 32)
				i++;
			if ((*promt)[i] && (*promt)[i] == '|')
			{
				(*count)--;
				return (1);
			}
			if (when_promt_ends_with_pipe(promt, i))
				return (1);
		}
		if ((*promt)[i])
			i++;
	}
	return (0);
}

void	free_pars(t_pars **pars, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(pars[i]->cmd);
		if (pars[i]->errfile)
			free(pars[i]->errfile);
		free(pars[i]);
		i++;
	}
	free(pars);
}

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
	*source = new_string;
	return (ret_string);
}
