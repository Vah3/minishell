/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:38 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/02 19:51:35 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//chi ogtagorcvum , bayc heto karoxa petq ga, pipe() bacelu hamar
/*int	**make_pipe_for_doc(int count)
{
	int i;
	int	**fd;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * (count + 1));
	if(!fd)
		return (0);
	fd[count] = 0;
	while (i < count)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2); // 2 te 3 stugel
		if (!fd[i])
		{
			while (i > 0)
			{
				i--;
				free(fd[i]);
			}
			free(fd);
		}
			return (0);
		i++;
	}
	return (fd);
}*/

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
	}
	if (write_docs(promt, doc_count, pars))
		return (1);
	return (0);
}

/*
	Writes in pipes and dups
*/
int	write_in_pipe_and_dup(t_pars **pars, int count, char *delim, int z)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (1);
	while (1)
	{
		line = readline(">");
		if (ft_strncmp(delim, line, ft_strlen(line)) == 0)
		{
			count--;
			break ;
		}
		if (write(fd[1], line, ft_strlen(line)) == -1)
			return (1);
		if (write(fd[1], "\n", 1) == -1)
			return (1);

	}
	if (close(fd[1]) == -1)
		return (1);
	(*pars)[z].isheredoc = dup(fd[0]);
	free(delim);
	return (0);
}

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
		skipquotes(&promt, &i);
		passwords(&promt, &i);
		if (promt[i] == '|')
			z++;
		if (promt[i] && promt[i] == '<' && promt[++i]
			&& promt[i] && promt[i] == '<' && promt[++i])
		{
			if (process_redirections(promt, &i, &j) == 1)
				return (1);
			delim = ft_substr(promt, j, i - 1);
			if (write_in_pipe_and_dup(pars, count, delim, z))
				return (1);
		}
	}
	return (0);
}
