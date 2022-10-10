/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:23:40 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/10 22:31:31 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_in_errno_and_free_exit(
	char **command, char *print, int code, char **cmd)
{
	int	i;

	i = 0;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command[0], 2);
	ft_putendl_fd(print, 2);
	while (command && command[i])
	{
		free(command[i]);
		free(cmd[i]);
		i++;
	}
	free(command);
	free(cmd);
	exit(code);
}

void	malloc_and_check(int count, int ***fd_, t_pars **pars, pid_t **id_)
{
	pid_t	*id;

	id = NULL;
	*id_ = NULL;
	if (init_pipe(fd_, count))
	{
		free_pars(pars);
		free(*fd_);
		exit(EXIT_FAILURE);
	}
	if (count > 1 && !(*fd_))
	{
		perror("fd");
		free_pars(pars);
		exit (EXIT_FAILURE);
	}
	id = (pid_t *)malloc(sizeof(pid_t) * count);
	if (!id)
	{
		perror("malloc failed");
		free_pars(pars);
		free(*fd_);
		exit (EXIT_FAILURE);
	}
	*id_ = id;
}

int	free_and_close(int (*fd)[2], int count, t_pars **pars, pid_t *id)
{
	close_pipes(fd, count);
	fr(pars, fd, id, count);
	return (1);
}

void	clear_spaces_if_all_are_spaces(char **line)
{
	int		i;
	char	*line_;
	char	*delim;

	i = 0;
	line_ = *line;
	delim = NULL;
	while (line_ && line_[i] == 32)
		i++;
	if (line_ && !line_[i])
		delim = ft_trim_substr(line, 0, i);
	free(delim);
}

int	do_parsing(char **line, t_pars **pars)
{
	int		i;
	int		work;
	char	*input;

	i = 0;
	input = *line;
	while (input && input[i])
	{
		skipquotes(&input, &i);
		work = 1;
		if (input && input[i]
			&& if_here_doc(&input, &((*pars)->fileordoc), &i, &work))
			return (FAILURE);
		if (input && input[i] && if_append_file(&input, pars, &i, &work))
			return (FAILURE);
		if (input && input[i] && if_in_file(&input, pars, &i, &work))
			return (FAILURE);
		if (input && input[i] && if_out_file(&input, pars, &i, &work))
			return (FAILURE);
		if (input && input[i] && work)
			i++;
	}
	*line = input;
	return (SUCCESS);
}
