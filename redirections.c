/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:42:36 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/25 10:03:03 by root             ###   ########.fr       */
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

int	lexer(char **promt, t_pars ***pars)
{
	int		i;
	int		pipe_i;
	char	**input;
	int		prev_ifs_not_worked;

	i = 0;
	pipe_i = 0;
	input = ft_split(*promt, '|');
	while(input && input[pipe_i])
	{
		while (input[pipe_i][i])
		{
			skipquotes(promt, &i);
			prev_ifs_not_worked = 1;
			if (input[pipe_i][i] && if_here_doc(&(input[pipe_i]), &((*pars)[pipe_i])->fileordoc, &i, &prev_ifs_not_worked))
				return (FAILURE);
			if (input[pipe_i][i] && if_append_file(&(input[pipe_i]), &((*pars)[pipe_i]), &i, &prev_ifs_not_worked))
				return (FAILURE);
			if (input[pipe_i][i] && if_in_file(&(input[pipe_i]), &((*pars)[pipe_i]), &i, &prev_ifs_not_worked))
				return (FAILURE);
			if (input[pipe_i][i] && if_out_file(&(input[pipe_i]), &((*pars)[pipe_i]), &i, &prev_ifs_not_worked))
				return (FAILURE);
			if (input[pipe_i][i] && prev_ifs_not_worked)
				i++;
		}
		(*pars)[pipe_i]->cmd = ft_strdup(input[pipe_i]);
		free(input[pipe_i]);
		pipe_i++;
		i = 0;
	}
	if(input)
	free(input);
	return (SUCCESS);
}
