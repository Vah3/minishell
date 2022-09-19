/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:03:32 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/08 17:12:39 by vagevorg         ###   ########.fr       */
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
			while (line[++i] && line[i] != '\'')
				;
			flag = (line[i] == '\0');
		}
		if (line[i] == '"')
		{
			while (line[++i] && line[i] != '"')
				;
			flag = (line[i] == '\0');
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
