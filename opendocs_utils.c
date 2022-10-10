/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:17:05 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/10 22:22:22 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *err_message, int err_code)
{
	ft_putstr_fd(err_message, 2);
	return (err_code);
}

int	correct_delim(char *promt, int i)
{
	if (promt[i] && promt[i] != 32
		&& promt[i] != '|' && promt[i] != '<' && promt[i] != '>')
		return (1);
	return (0);
}

void	skips_and_detect_pipe(char **promt, int *i, int *z)
{
	skipquotes(promt, i);
	if ((*promt)[*i] == '|')
		(*z)++;
}
/*
	Writes in pipes and dups -- see utils.c
*/

void	process_redirections(char *promt, int *i, int *j)
{
	while (promt && promt[*i] && promt[*i] == 32)
		(*i)++;
	*j = *i;
	if (promt && (promt[*i] == '|' || promt[*i] == '<' || promt[*i] == '>'))
		return ;
	skipquotes(&promt, i);
	while (correct_delim(promt, *i))
		(*i)++;
}

int	close_pipe_and_free_delim(int fd[2], int z, t_pars **pars, char *delim)
{
	if (close(fd[1]) == -1)
		return (FAILURE);
	pars[z]->isheredoc = dup(fd[0]);
	free(delim);
	return (SUCCESS);
}
