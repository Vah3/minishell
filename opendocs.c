/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:38 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/18 15:31:51 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *err_message, int err_code)
{
	ft_putstr_fd(err_message, 2);
	return (err_code);
}

int	openheredoc(char *promt, t_pars **pars)
{
	int	i;
	int	doc_count;

	i = 0;
	doc_count = 0;
	while (promt[i])
	{
		skipquotes(&promt, &i);
		if (promt[i] && promt[i + 1] && promt[i] == '<' && promt[i + 1] == '<'
			&& promt[i++] && promt[i++])
		{
			while (promt[i] && promt[i] == 32)
				i++;
			if (promt[i] == '\0')
				return (FAILURE);
			if (promt[i] == '|' || promt[i] == '<' || promt[i] == '>')
				continue ;
			doc_count++;
		}
		if (promt[i])
			i++;
	}
	if (write_docs(promt, doc_count, pars))
		return (1);
	return (0);
}

/*
	Writes in pipes and dups -- see utils.c
*/

void	process_redirections(char *promt, int *i, int *j)
{
	while (promt[*i] && promt[*i] == 32)
		(*i)++;
	*j = *i;
	if (promt[*i] == '|' || promt[*i] == '<' || promt[*i] == '>')
		return ;
	while (promt[*i] && promt[*i] != 32)
		(*i)++;
}

void	skips_and_detect_pipe(char **promt, int *i, int *z)
{
	skipquotes(promt, i);
	if ((*promt)[*i] == '|')
		(*z)++;
}

int	write_docs(char *promt, int count, t_pars **pars)
{
	int		i;
	int		j;
	int		z;
	char	*delim;

	z = 0;
	i = 0;
	while (promt[i])
	{
		skips_and_detect_pipe(&promt, &i, &z);
		if (promt[i] && promt[i] == '<' && promt[++i]
			&& promt[i] && promt[i] == '<' && promt[++i])
		{
			process_redirections(promt, &i, &j);
			if (i == j)
				continue ;
			delim = ft_substr(promt, j, i - j);
			if (write_in_pipe_and_dup(pars, count, delim, z))
				return (1);
		}
		if (promt[i])
			i++ ;
	}
	return (0);
}
