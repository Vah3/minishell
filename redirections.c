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
	// printf("------------------%x\n",&(*pars)[k]->fileordoc);
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
			if (c == '<')
				(*pars)[k]->fileordoc = 0;
			if (trimspaces(promt, &i, &j, c))
				return (2);
			iffiles(promt, &i, &j);
			if(opener(promt, j, i, c, &((*pars)[k])))
				return(0);
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
//	if (!(*promt))
//		return (0);
	return(1);
}

int	if_append_file(char **promt, t_pars **pars, int *i, int *j)
{
	char *filename;

	if ((*promt)[*i] && (*promt)[*i] == '>'  && (*promt)[(*i) + 1] && (*promt)[(*i) + 1] == '>')
	{
		*i += 2;
		if(trimspaces(promt, i, j, '>'))
			return (2);
		iffiles(promt, i, j);
		filename = ft_trim_substr(promt, *j, *i);
		open_out_file(filename, pars, 'a');
		free(filename);
		*i = *j;
	}
//	if (!(*promt))
//		return (0);
	return(1);
}

