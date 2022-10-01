/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:38 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/25 09:58:31 by root             ###   ########.fr       */
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
	if(promt[i] && promt[i] != 32 && promt[i] != '|' && promt[i] != '<' && promt[i] != '>')
		return (1);
	return (0);
}

int	write_docs(char *promt, t_pars **pars)
{
	int		i;
	int		j;
	int		z;
	char	*delim;

	z = 0;
	i = 0;
	
	while (promt[i] != '\0')
	{
		skips_and_detect_pipe(&promt, &i, &z);
		if (promt[i] && promt[i] == '<' && promt[++i]
			&& promt[i] && promt[i] == '<' && promt[++i])
		{
			process_redirections(promt, &i, &j);
			if (i == j)
				continue ;
			delim = ft_substr(promt, j, i - j);
			if (write_in_pipe_and_dup(pars, delim, z))
				return (1);
		}
		else if (promt[i] != '\0')
			i++;
	}
	return (0);
}

int	openheredoc(char *promt, t_pars **pars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (promt[i])
	{
		skipquotes(&promt, &i);
		if (promt[i] && promt[i + 1] && promt[i] == '<' && promt[i + 1] == '<'
			&& promt[i++] && promt[i++])
		{
			while (promt[i] && promt[i] == 32)
				i++;
			while (correct_delim(promt, i))
				i++;
			count++;
			if (count > 16)
			exit (2);
		}
		if (promt[i])
			i++;
	}	if (write_docs(promt, pars))
		return (1);
	return (0);
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

void	skips_and_detect_pipe(char **promt, int *i, int *z)
{
	skipquotes(promt, i);
	if ((*promt)[*i] == '|')
		(*z)++;
}

// void	handle3(int i)
// {
// 	(void) i;
// 	status = -1;
// }


// int	write_docs(char *promt, t_pars **pars)
// {
// 	int		i;
// 	int		j;
// 	int		z;
// 	char	*delim;

// 	z = 0;
// 	i = 0;
// 	signal(SIGINT, handle3);
	
// 	while (promt[i] != '\0')
// 	{
// 		skips_and_detect_pipe(&promt, &i, &z);
// 		if(status == -1)
// 			break ;
// 		if (promt[i] && promt[i] == '<' && promt[++i]
// 			&& promt[i] && promt[i] == '<' && promt[++i])
// 		{
// 			process_redirections(promt, &i, &j);
// 			if (i == j)
// 				continue ;
// 			delim = ft_substr(promt, j, i - j);
// 			if (write_in_pipe_and_dup(pars, delim, z))
// 				return (1);
// 		}
// 		else if (promt[i] != '\0')
// 			i++;
// 	}
// 	if (status == -1)
// 	{
// 		status = 1;
// 		return (1);
// 	}
// 	return (0);
// }
