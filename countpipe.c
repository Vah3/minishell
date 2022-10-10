/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countpipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:07:22 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/10 21:13:12 by vagevorg         ###   ########.fr       */
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
