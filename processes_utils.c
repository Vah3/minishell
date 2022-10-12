/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:23:40 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/12 20:03:34 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	code_and_print(int *code, char **print)
{
	if (*code == 128)
		*print = " is a directory";
	else if (*code == 129)
		*print = " No such file or directory";
	else if (*code == 130)
		*print = " Command not found";
	else if (*code == 131)
		*print = " Permission denied";
	if (*code == 128 || *code == 131)
		*code = 126;
	if (*code == 129 || *code == 130)
		*code = 127;
}

void	print_in_errno_and_free_exit(
	char **command, int code, char **cmd, t_env *env)
{
	int		i;
	char	*print;

	print = NULL;
	i = 0;
	code_and_print(&code, &print);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command[0], 2);
	ft_putendl_fd(print, 2);
	while (command && command[i])
	{
		free(command[i]);
		if (_getenv(env, "PATH"))
			free(cmd[i]);
		i++;
	}
	free(command);
	free(cmd);
	exit(code);
}

int	malloc_and_check(int count, int ***fd_, t_pars **pars, pid_t **id_)
{
	pid_t	*id;

	id = NULL;
	*id_ = NULL;
	if (init_pipe(fd_, count))
	{
		free_pars(pars);
		return (FAILURE);
	}
	if (count > 1 && !(*fd_))
	{
		perror("fd");
		free_pars(pars);
		return (FAILURE);
	}
	id = (pid_t *)malloc(sizeof(pid_t) * count);
	if (!id)
	{
		perror("malloc failed");
		free_pars(pars);
		free(*fd_);
		return (FAILURE);
	}
	*id_ = id;
	return (SUCCESS);
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
