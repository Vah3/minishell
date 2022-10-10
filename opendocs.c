/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:38 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/10 21:02:10 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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
	while (promt && promt[i])
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
	}
	return (write_docs(promt, pars));
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

int	write_in_pipe_and_dup(t_pars **pars, char *delim, int z)
{
	int		fd[2];
	char	*line;
	int		expand_or_not;
	int		input;

	if (pipe(fd) == -1)
		return (FAILURE);
	expand_or_not = clearquotes(&delim);
	input = dup(0);
	signal(SIGINT, handle2);
	while (1)
	{
		line = readline(">");
		expand_if_does_not_have_quotes(&line, expand_or_not, pars[0]);
		if (checking_line(line, delim))
			break ;
		if (write(fd[1], line, ft_strlen(line)) == -1)
			return (FAILURE);
		if (write(fd[1], "\n", 1) == -1)
			return (FAILURE);
		free(line);
	}
	return (close_pipe_and_free_delim(fd, z, pars, delim)
		|| set_status_back(input));
}

int	set_status_back(int input_fd)
{
	if (g_status == -1)
	{
		g_status = 1;
		dup2(input_fd, 0);
		signal(SIGINT, handle4);
		return (1);
	}
	else
		g_status = 0;
	return (0);
}

int	close_pipe_and_free_delim(int fd[2], int z, t_pars **pars, char *delim)
{
	if (close(fd[1]) == -1)
		return (FAILURE);
	pars[z]->isheredoc = dup(fd[0]);
	free(delim);
	return (SUCCESS);
}

int	checking_line(char *line, char *delim)
{
	if (g_status == -1)
		return (1);
	if (!line)
	{
		g_status = 0;
		return (1);
	}
	if (ft_strncmp(delim, line, ft_strlen(line)) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}
