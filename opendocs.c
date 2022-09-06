/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:38 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/06 16:38:53 by vagevorg         ###   ########.fr       */
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

	i = -1;
	doc_count = 0;
	while (promt[++i])
	{
		skipquotes(&promt, &i);
		passwords(&promt, &i);
		if (promt[i] && promt[i] == '<' && promt[++i]
			&& promt[i] && promt[i] == '<' && promt[++i])
		{
			doc_count++;
			while (promt[i] && promt[i] == 32)
				i++;
			if (promt[i] == '\0' || promt[i] == '|'
				|| promt[i] == '<' || promt[i] == '>')
				return (ft_error("Syntax error\n", 1));
		}
		if (!promt[i])
			break ;
	}
	if (write_docs(promt, doc_count, pars))
		return (1);
	return (0);
}

/*
	Writes in pipes and dups -- see utils.c
*/

int	process_redirections(char *prompt, int *i, int *j)
{
	while (prompt[*i] && prompt[*i] == 32)
		(*i)++;
	if (!prompt[*i])
		return (ft_error("Syntax error\n", 1));
	*j = *i;
	while (prompt[*i] && prompt[*i] != 32)
		(*i)++;
	return (0);
}

void	skips_and_detect_pipe(char **promt, int *i, int *z)
{
	skipquotes(promt, i);
	passwords(promt, i);
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
	i = -1;
	while (promt[++i])
	{
		skips_and_detect_pipe(&promt, &i, &z);
		if (promt[i] && promt[i] == '<' && promt[++i]
			&& promt[i] && promt[i] == '<' && promt[++i])
		{
			if (process_redirections(promt, &i, &j) == 1)
				return (1);
			delim = ft_substr(promt, j, i - j);
			if (write_in_pipe_and_dup(pars, count, delim, z))
				return (1);
		}
		if (!promt[i])
			break ;
	}
	return (0);
}
