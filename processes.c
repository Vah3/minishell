/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:44:28 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/10 19:45:26 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	close_pipes(int (*fd)[2], int count)
{
	int	j;

	j = 0;
	while (j < count - 1)
	{
		if (close(fd[j][0]) == -1)
		{
			perror("CLOSE FAILED");
			return (FAILURE);
		}
		if (close(fd[j][1]) == -1)
		{
			perror("CLOSE FAILED");
			return (FAILURE);
		}
		j++;
	}
	return (SUCCESS);
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

int	do_fork(pid_t **id, int i)
{
	int	i_;

	i_ = 0;
	(*id)[i] = fork();
	if ((*id)[i] == -1)
	{
		while (i_ < i)
		{
			if (kill((*id)[i_], SIGKILL))
				perror("kill");
			if (wait(NULL) < 0)
				perror("");
			i_++;
		}
		g_status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

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

void	do_execve(t_pars *pars, char **env, t_env *env_)
{
	char	**cmd;
	char	*line;
	char	**command;

	cmd = pars->exec_cmd;
	line = pars->cmd;
	line = get_correct_cmd(line);
	command = ft_split(line, 32);
	if (there_is_builtin(line))
		exit(call_builtin(&pars, line, there_is_builtin(line), env_));
	if (cmd && cmd[0])
		execve(cmd[0], cmd, env);
	if (cmd && cmd[0] && opendir(cmd[0]))
		print_in_errno_and_free_exit(command, " is a directory", 126, cmd);
	if (cmd && !cmd[0] && ft_strchr(command[0], '/'))
		print_in_errno_and_free_exit
		(command, " No such file or directory", 127, cmd);
	else if (cmd && (!cmd[0] || !ft_strchr(command[0], '/')))
		print_in_errno_and_free_exit
			(command, " Command not found", 127, cmd);
	if (cmd && cmd[0] && access(cmd[0], F_OK) == 0
		&& access(cmd[0], X_OK) == -1)
		print_in_errno_and_free_exit(command, " Permission denied", 126, cmd);
	exit(g_status);
}

void	sig_and_set_attr(pid_t *id, int i)
{
	struct termios	a;

	if (id[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		tcgetattr(0, &a);
		a.c_lflag |= ECHOCTL;
		tcsetattr(0, 0, &a);
	}
}

int	free_and_close(int (*fd)[2], int count, t_pars **pars, pid_t *id)
{
	close_pipes(fd, count);
	fr(pars, fd, id, count);
	return (1);
}

void	open_processes(int count, t_pars **pars, char **env, t_env *env_)
{
	int		i;
	int		(*fd)[2];
	pid_t	*id;

	i = -1;
	malloc_and_check(count, (int ***)&fd, pars, &id);
	while (++i < count)
	{
		if (do_fork(&id, i) && free_and_close(fd, count, pars, id))
			return ;
		sig_and_set_attr(id, i);
		if (id[i] == 0)
			make_cmd(pars[i], env);
		if (id[i] == 0 && count == 2 && single_pipe(i, fd, pars[i]))
			exit (EXIT_FAILURE);
		if (id[i] == 0 && count > 2 && multi_pipe(i, fd, count, pars[i]))
			exit (EXIT_FAILURE);
		if (id[i] == 0 && count == 1)
			without_pipes(pars, fd, id, count);
		if (id[i] == 0)
			do_execve(pars[i], env, env_);
	}
	wait_(fd, id, count);
	fr(pars, fd, id, count);
}
