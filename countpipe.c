/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countpipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:07:22 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/12 19:45:06 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	skip_index_until_pipe(char **promt, int *i)
{
	while ((*promt)[*i] && (*promt)[*i] != '|')
	{
		skipquotes(promt, i);
		if ((*promt)[*i])
			(*i)++;
	}
}

int	get_new_line(char **newline)
{
	while (1)
	{
		*newline = readline(">");
		if (!(*newline) && g_status != -1)
		{		
			ft_putendl_fd(" minishell: syntax error: "
				"unexpected end of file", 2);
			g_status = 258;
			return (1);
		}
		clear_spaces_if_all_are_spaces(newline);
		if (!(*newline) && g_status != -1)
			continue ;
		break ;
	}
	if (not_found_second_quote(*newline)
		|| only_pipe(*newline) || check_redirections(*newline))
	{
		free(*newline);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	when_promt_ends_with_pipe(char **promt, int i)
{
	char	*newline;
	int		stdin_;

	stdin_ = dup(STDIN_FILENO);
	newline = NULL;
	signal(SIGINT, handle2);
	if (!(*promt)[i])
	{
		if (get_new_line(&newline))
			return (FAILURE);
		*promt = ft_strjoin(*promt, " ");
		*promt = ft_strjoin(*promt, newline);
		free(newline);
		newline = NULL;
	}
	if (set_status_back(stdin_))
		return (1);
	signal(SIGINT, handle4);
	return (0);
}

int	check_pipes_count(char **promt, int *count)
{
	int		i;

	*count = 1;
	i = 0;
	while (*promt && (*promt)[i])
	{
		skip_index_until_pipe(promt, &i);
		if ((*promt)[i] && (*promt)[i] == '|')
		{
			(*count)++;
			i++;
			while ((*promt)[i] && (*promt)[i] == 32)
				i++;
			if ((*promt)[i] && (*promt)[i] == '|')
				return (1);
			if (when_promt_ends_with_pipe(promt, i))
				return (1);
		}
		if ((*promt)[i])
			i++;
	}
	return (0);
}

void	free_pars(t_pars **pars)
{
	int	i;

	i = 0;
	while (pars && pars[i])
	{
		free(pars[i]->cmd);
		if (pars[i]->errfile)
			free(pars[i]->errfile);
		free(pars[i]);
		i++;
	}
	free(pars);
}
