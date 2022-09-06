/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:42:36 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/05 10:25:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char **promt, t_pars ***pars, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	j = 0;
	while ((*promt)[i])
	{
		skipquotes(promt, &i);
		passwords(promt, &i);
		if((*promt)[i] && (*promt)[i] == '|')
			k++;
		if(c == '<' && if_here_doc(promt, &((*pars)[k])->fileordoc, &i, &j) == 2)
			return (1);
		if(c == '>' && if_append_file(promt, &((*pars)[k]), &i, &j) == 2)
			return (1);
		if ((*promt)[i] && (*promt)[i] == c)
		{
			i++;
			if (trimspaces(promt, &i, &j, c))
				return (2);
			iffiles(promt, &i, &j);
			if (c == '<')
			{
				(*pars)[k]->fileordoc = 0;
				open_in_file(&((*pars)[k]),promt, j , i);
			}
			else if (c == '>')
			{
				(*pars)[k]->app_or_trunc = 1;
				open_out_file(&((*pars)[k]), promt, j, i);
			}
			i = j;
		}
		if((*promt)[i])
			i++;
	}
	return (1);
}

int	if_here_doc(char **promt,int *fileordoc, int *i, int *j)
{
	char *delim;

	if ((*promt)[*i] && (*promt)[*i] == '<'  && (*promt)[(*i) + 1] && (*promt)[(*i) + 1] == '<')
	{
		*i += 2;
		if(trimspaces(promt, i, j, '<'))
			return (2);
		iffiles(promt, i, j);
		delim = ft_trim_substr(promt, *j, *i);
		free(delim);
		*fileordoc = 1;
		*i = *j;
	}
	return(1);
}

int	if_append_file(char **promt, t_pars **pars, int *i, int *j)
{
	if ((*promt)[*i] && (*promt)[*i] == '>'  && (*promt)[(*i) + 1] && (*promt)[(*i) + 1] == '>')
	{
		*i += 2;
		if(trimspaces(promt, i, j, '>'))
			return (2);
		iffiles(promt, i, j);
		(*pars)->app_or_trunc = 0;
		open_out_file(pars, promt, *j , *i);
		*i = *j;
	}
	return(1);
}

