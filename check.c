/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:03:32 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/09 18:48:35 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int status;

static int	check_error(char *promt, int *i)
{
	while (promt[*i] && promt[*i] == 32)
		(*i)++;
	if (!promt[*i])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token  `newline'", 2);
		status = 258;
		return (FAILURE);
	}
	else if (promt[*i] == '<' || promt[*i] == '|' || promt[*i] == '>')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(promt[*i], 2);
		ft_putendl_fd("'", 2);
		status = 258;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_redirections(char *promt)
{
	int	i;

	i = 0;
	while (promt && promt[i])
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
		if(promt[i])
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
	while (line && line[i] != '\0')
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
		ft_putendl_fd("minishell: syntax error: not found second quote", 2);
	return (flag);
}

int	only_pipe(char *prompt)
{
	int	i;

	i = 0;
//	while (prompt && prompt[++i] && (prompt[i] == ' ' || prompt[i] == '\t'))
//		;
	while(prompt && prompt[i])
	{
		while (prompt && prompt[i] && prompt[i] != '|')
			i++;
		if (prompt && prompt[i] && prompt[++i] && prompt[i] == '|')
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
			status = 258;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
