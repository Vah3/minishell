/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:44:28 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/20 20:54:50 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd_id(int (*fd)[2], pid_t *id, int count)
{
	if (count > 1)
		free(fd);
	free(id);
}

int	free_everything(t_pars **pars, int (*fd)[2], pid_t *id, int count)
{
	free_fd_id(fd, id, count);
	free_pars(pars, count);
	return (1);
}

static int	make_cmd(t_pars *pars, char ***cmd, char **env)
{
	char	**command;
	int		j;

	j = 0;
	command = NULL;
	if (pars->cmd != NULL && pars->errfile == NULL)
	{
		command = ft_split(pars->cmd, 32);
		if (!command)
			return (FAILURE);
		while (command[j])
		{	
			command[j] = get_correct_cmd(command[j]);
			j++;
		}
		check_make(&command[0], env);
		*cmd = command;
	}
	return (SUCCESS);
}	

static	void	without_pipes(t_pars **pars, int (*fd)[2], pid_t *id, int count)
{
	if (pars[0]->errfile)
	{
		printf("minishell: %s : %s\n",
			pars[0]->errfile, strerror(pars[0]->errnum));
		free_everything(pars, fd, id, count);
		exit(EXIT_FAILURE);
	}
	if (pars[0]->outfilefd == -1 && free_everything(pars, fd, id, count))
		exit(EXIT_FAILURE);
	if (check_out_or_input(pars[0]) == FAILURE
		&& free_everything(pars, fd, id, count))
		exit(EXIT_FAILURE);
}

void	wait_(int *status, int (*fd)[2], pid_t *id, int count)
{
	int	j;

	j = 0;
	close_pipes(fd, count);
	while (j < count)
	{
		waitpid(id[j++], status, 0);
		if (WIFEXITED (*status))
			*status = WEXITSTATUS(*status);
	}
}

void	malloc_and_check(int count, int (*fd)[2], t_pars **pars, pid_t **id_)
{
	pid_t	*id;

	id = NULL;
	if (count > 1 && !fd)
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
		free(fd);
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

void	do_execve(char **cmd, char **env, t_pars *pars)
{
	execve(cmd[0], cmd, env);
	if (ft_strlen(pars->cmd) == 0)
		exit(0);
	printf("%s\n", strerror(errno));
	exit(126);
}

void	open_processes(int count, t_pars **pars, char **env, int *status)
{
	int		i;
	int		(*fd)[2];
	pid_t	*id;

	i = -1;
	init_pipe((int ***)&fd, count);
	malloc_and_check(count, fd, pars, &id);
	while (++i < count)
	{
		do_fork(&id, i);
		if (id[i] == 0)
		{
			if (make_cmd(pars[i], &(pars[i]->exec_cmd), env)
				&& free_everything(pars, fd, id, count))
				exit(EXIT_FAILURE);
			if (count == 2 && single_pipe(i, fd, pars[i])
				&& free_everything(pars, fd, id, count))
				exit (EXIT_FAILURE);
			if (count > 2 && multi_pipe(i, fd, count, pars[i])
				&& free_everything(pars, fd, id, count))
				exit (EXIT_FAILURE);
			else if (count == 1)
				without_pipes(pars, fd, id, count);
			do_execve(pars[i]->exec_cmd, env, pars[i]);
		}
	}
	wait_(status, fd, id, count);
	free_everything(pars, fd, id,count);
}
