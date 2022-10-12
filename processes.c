/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:44:28 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/12 20:43:00 by vagevorg         ###   ########.fr       */
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

int	do_fork(pid_t **id, int i)
{
	(*id)[i] = fork();
	if ((*id)[i] == -1)
	{
		perror("forks failed");
		while (i > 0)
		{
			i--;
			if (kill((*id)[i], SIGTERM))
				perror("kill");
			waitpid((*id)[i], NULL, 0);
		}
		g_status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

void	do_execve(t_pars *pars, char **env, t_env *env_)
{
	char	**cmd;
	char	*line;
	char	**command;

	cmd = pars->exec_cmd;
	line = pars->cmd;
	command = ft_split(line, 32);
	if (there_is_builtin(line))
		exit(call_builtin(pars, line, there_is_builtin(line), env_));
	line = get_correct_cmd(line);
	if (cmd && cmd[0])
		execve(cmd[0], cmd, env);
	if (cmd && cmd[0] && opendir(cmd[0]))
		print_in_errno_and_free_exit(command, 128, cmd, env_);
	if (cmd && !cmd[0] && ft_strchr(command[0], '/'))
		print_in_errno_and_free_exit
		(command, 129, cmd, env_);
	else if (cmd && (!cmd[0] || !ft_strchr(command[0], '/')))
		print_in_errno_and_free_exit
			(command, 130, cmd, env_);
	if (cmd && cmd[0] && access(cmd[0], F_OK) == 0
		&& access(cmd[0], X_OK) == -1)
		print_in_errno_and_free_exit(command, 131, cmd, env_);
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

void	open_processes(int count, t_pars **pars, char **env, t_env *env_)
{
	int		i;
	int		(*fd)[2];
	pid_t	*id;

	i = -1;
	if (malloc_and_check(count, (int ***)&fd, pars, &id))
		return ;
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
