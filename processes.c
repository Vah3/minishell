/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:44:28 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/06 21:09:27 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int status;

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
			if(wait(NULL) < 0)
				perror("");
			i_++;
		}
		status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}


void	print_in_errno_and_free_exit(char **command, char *print, int code , char **cmd)
{
	int 	i;

	i = 0;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command[0], 2);
	ft_putendl_fd(print, 2);
	while(command && command[i])
	{
		free(command[i]);
		free(cmd[i]);
		i++;
	}
	free(command);
	free(cmd);
	exit(code);
}

typedef struct for_free
{
	int		(*fd)[2];
	pid_t	*id;
	t_pars **pars;
} t_free;

void	do_execve(t_pars *pars, char **env, t_env *env_, t_free *__fre)
{
	char	**cmd;
	char	*line;
	char	**command;

	cmd = pars->exec_cmd;
	line = pars->cmd;
	command = ft_split(line, 32);
	if (there_is_builtin(line))
		exit( call_builtin(line, there_is_builtin(line), env_));
	execve(cmd[0], cmd, env);
	if (cmd[0] && opendir(cmd[0]))
	{
		free(__fre->fd);
		free(__fre->id);
		free_pars(__fre->pars);
		print_in_errno_and_free_exit(command, " is a directory", 126, cmd);
	}
	if (!cmd[0] && ft_strchr(command[0], '/'))
		print_in_errno_and_free_exit(command, " No such file or directory", 127, cmd);
	else if (!cmd[0] || !ft_strchr(command[0], '/'))
		print_in_errno_and_free_exit(command, " Comomand not found", 127, cmd);
	if (cmd[0] && access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == -1)
		print_in_errno_and_free_exit(command, " Permission denied", 126, cmd);
	exit(0);
}



void	open_processes(int count, t_pars **pars, char **env, t_env *env_)
{
	int		i;
	int		(*fd)[2];
	pid_t	*id = NULL;
	struct termios a;
	t_free __fre;

	i = -1;

	malloc_and_check(count, (int ***)&fd, pars, &id);
	__fre.id = id;
	__fre.fd = fd;
	__fre.pars = pars;
	while (++i < count)
	{
		if(do_fork(&id, i))
		{
			close_pipes(fd, count);
			fr(pars, fd, id, count);
			return ;
		}
		if (id[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			tcgetattr(0, &a);
			a.c_lflag |= ECHOCTL;
			tcsetattr(0, 0, &a);
		}
		if (id[i] == 0 )
		 	make_cmd(pars[i], env);
		if (id[i] == 0 && count == 2 && single_pipe(i, fd, pars[i])
			&& fr(pars, fd, id, count))
			exit (EXIT_FAILURE);
		if (id[i] == 0 && count > 2 && multi_pipe(i, fd, count, pars[i])
			&& fr(pars, fd, id, count))
			exit (EXIT_FAILURE);
		if (id[i] == 0 && count == 1)
			without_pipes(pars, fd, id, count);
		if (id[i] == 0)
			do_execve(pars[i], env, env_, &__fre);
	}
	wait_(fd, id, count);
	fr(pars, fd, id, count);
}
