/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:44:28 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/21 15:21:24 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	init_pipe(fd_, count);
	if (count > 1 && !(*fd_))
	{
		perror("fd");
		free_pars(pars, count);
		exit (EXIT_FAILURE);
	}
	id = (pid_t *)malloc(sizeof(pid_t) * count);
	if (!id)
	{
		perror("malloc failed");
		free_pars(pars, count);
		free(*fd_);
		exit (EXIT_FAILURE);
	}
	*id_ = id;
}

void	do_fork(pid_t **id, int i)
{
	(*id)[i] = fork();
	if ((*id)[i] == -1)
	{
		perror("forks failed");
		exit(EXIT_FAILURE);
	}
}

int	do_execve(char **cmd, char **env, t_pars *pars)
{
	execve(cmd[0], cmd, env);
	if (ft_strlen(pars->cmd) == 0)
		exit(0);
	exit(126);
	return (1);
}

void	open_processes(int count, t_pars **pars, char **env, int *status)
{
	int		i;
	int		(*fd)[2];
	pid_t	*id;

	i = -1;
	malloc_and_check(count, (int ***)&fd, pars, &id);
	while (++i < count)
	{
		do_fork(&id, i);
		if (id[i] == 0 )
			make_cmd(pars[i], env);
		if (id[i] == 0 && count == 2 && single_pipe(i, fd, pars[i]))
			//&& fr(pars, fd, id, count))
			exit (EXIT_FAILURE);
		if (id[i] == 0 && count > 2 && multi_pipe(i, fd, count, pars[i]))
			//&& fr(pars, fd, id, count))
			exit (EXIT_FAILURE);
		if (id[i] == 0 && count == 1)
			without_pipes(pars, fd, id, count);
		if (id[i] == 0)
			do_execve((pars[i])->exec_cmd, env, pars[i]);
	}
	wait_(status, fd, id, count);
	fr(pars, fd, id, count);
}
