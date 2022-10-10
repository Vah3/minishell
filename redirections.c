/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:42:36 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/10 20:40:25 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_in_file(char **promt, t_pars **pars, int *i, int *z)
{
	int	j;

	j = 0;
	if ((*promt)[*i] && (*promt)[*i] == '<'
		&& (*promt)[(*i) + 1] && (*promt)[(*i) + 1] != '<')
	{
		(*i)++;
		if (trimspaces(promt, i, '<'))
			return (FAILURE);
		j = *i;
		iffiles(promt, i);
		open_in_file(pars, promt, j, *i);
		*i = j;
		*z = 0;
	}
	return (SUCCESS);
}

static int	if_out_file(char **promt, t_pars **pars, int *i, int *z)
{
	int	j;

	j = 0;
	if ((*promt)[*i] && (*promt)[*i] == '>'
		&& (*promt)[(*i) + 1] && (*promt)[(*i) + 1] != '>')
	{
		(*i)++;
		if (trimspaces(promt, i, '>'))
			return (FAILURE);
		j = *i;
		iffiles(promt, i);
		(*pars)->app_or_trunc = 1;
		open_out_file(pars, promt, j, *i);
		*i = j;
		*z = 0;
	}
	return (SUCCESS);
}

static int	if_here_doc(char **promt, int *fileordoc, int *i, int *z)
{
	char	*delim;
	int		j;

	j = 0;
	if ((*promt)[*i] && (*promt)[*i] == '<'
		&& (*promt)[(*i) + 1] && (*promt)[(*i) + 1] == '<')
	{
		*i += 2;
		if (trimspaces(promt, i, '<'))
			return (FAILURE);
		j = *i;
		iffiles(promt, i);
		delim = ft_trim_substr(promt, j, *i);
		free(delim);
		*fileordoc = 1;
		*i = j;
		*z = 0;
	}
	return (SUCCESS);
}

static int	if_append_file(char **promt, t_pars **pars, int *i, int *z)
{
	int	j;

	j = 0;
	if ((*promt)[*i] && (*promt)[*i] == '>'
		&& (*promt)[(*i) + 1] && (*promt)[(*i) + 1] == '>')
	{
		*i += 2;
		if (trimspaces(promt, i, '>'))
			return (FAILURE);
		j = *i;
		iffiles(promt, i);
		(*pars)->app_or_trunc = 0;
		open_out_file(pars, promt, j, *i);
		*i = j;
		*z = 0;
	}
	return (SUCCESS);
}

void	clear_spaces_if_all_are_spaces(char **line)
{
	int		i;
	char	*line_;
	char	*delim;

	i = 0;
	line_ = *line;
	delim = NULL;
	while (line_ && line_[i] == 32)
		i++;
	if (line_ && !line_[i])
		delim = ft_trim_substr(line, 0, i);
	free(delim);
}

int	do_parsing(char **line, t_pars **pars)
{
	int		i;
	int		work;
	char	*input;

	i = 0;
	input = *line;
	while (input && input[i])
	{
		skipquotes(&input, &i);
		work = 1;
		if (input && input[i]
			&& if_here_doc(&input, &((*pars)->fileordoc), &i, &work))
			return (FAILURE);
		if (input && input[i] && if_append_file(&input, pars, &i, &work))
			return (FAILURE);
		if (input && input[i] && if_in_file(&input, pars, &i, &work))
			return (FAILURE);
		if (input && input[i] && if_out_file(&input, pars, &i, &work))
			return (FAILURE);
		if (input && input[i] && work)
			i++;
	}
	*line = input;
	return (SUCCESS);
}

int	lexer(char **promt, t_pars **pars)
{
	int		pipe_i;
	char	**input;

	pipe_i = 0;
	input = NULL;
	input = ft_split(*promt, '|');
	while (input && input[pipe_i])
	{
		do_parsing(&(input[pipe_i]), &(pars[pipe_i]));
		clear_spaces_if_all_are_spaces(&(input[pipe_i]));
		pars[pipe_i]->cmd = ft_strdup(input[pipe_i]);
		free(input[pipe_i]);
		pipe_i++;
	}
	free(input);
	return (SUCCESS);
}
