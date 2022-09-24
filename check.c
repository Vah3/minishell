/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:03:32 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/19 20:03:38 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_error(char *promt, int *i)
{
	while (promt[*i] && promt[*i] == 32)
		(*i)++;
	if (!promt[*i])
	{
		printf ("%s", "syntax error near unexpected token `newline'\n");
		return (FAILURE);
	}
	else if (promt[*i] == '<' || promt[*i] == '|' || promt[*i] == '>')
	{
		printf ("syntax error near unexpected token `%c'\n", promt[*i]);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_redirections(char *promt)
{
	int	i;

	i = 0;
	while (promt[i])
	{
		skipquotes(&promt, &i);
		if ((promt[i] && promt[i] == '<'
				&& promt[i + 1] && promt[i + 1] == '<')
			|| (promt[i] && promt[i] == '>'
				&& promt[i + 1] && promt[i + 1] == '>'))
		{
			i += 2;
			if (check_error(promt, &i))
				return (FAILURE);
		}
		else if (promt[i] && (promt[i] == '>' || promt[i] == '<'))
		{
			i++;
			if (check_error(promt, &i))
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

void	find_quote(char *line, int *i, int *flag, int which)
{	
	if (which == 1)
	{
		while (line[++(*i)] && line[(*i)] != '\'')
			if (line[(*i)] == '\\')
				*i += 1;
		*flag = (line[(*i)] == '\0');
	}
	else if (which == 2)
	{
		while (line[++(*i)] && line[(*i)] != '"' && line[(*i) - 1] != '\\')
			if (line[(*i)] == '\\')
				*i += 1;
		*flag = (line[(*i)] == '\0');
	}
}

int	not_found_second_quote(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			if (i > 0 && line[i - 1] == '\\' && i++)
				continue ;
			find_quote(line, &i, &flag, 1);
		}
		if (line[i] == '"')
		{
			if (i > 0 && line[i - 1] == '\\' && i++)
				continue ;
			find_quote(line, &i, &flag, 2);
		}
		if (line[i])
			i++;
	}
	if (flag)
		printf("NOT FOUND SECOND QUOTE\n");
	return (flag);
}

int	only_pipe(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i] && (prompt[i] == ' ' || prompt[i] == '\t'))
		;
	if (prompt[i] == '|')
	{
		printf ("syntax error near unexpected token `|'\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
