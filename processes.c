/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:44:28 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/07 14:52:42 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_fd_id(int (*fd)[2], pid_t	*id,  int count)
{
	if(count > 1)
		free(fd);
	free(id);
}

int	open_processes(int	count, t_pars **pars, char **env)
{
	int		i;
	pid_t	*id;
	int		(*fd)[2];
	int 	j = 0;
	char 	**cmd = NULL;

	i = 0;
	init_pipe((int ***)&(fd),  count);
	if (count > 1 && !fd)
	{
		free_pars(pars, count);
		exit (EXIT_FAILURE);
	}
	id = (pid_t *)malloc(sizeof(pid_t) * count);
	if (!id)
	{
		free_pars(pars, count);
		free(fd);
		exit (EXIT_FAILURE);
	}
	while (i < count)
	{
		id[i] = fork();
		if (id[i] == -1)
		{
			perror("forks failed");
			free_fd_id(fd, id, count);
			free_pars(pars, count);
			exit(EXIT_FAILURE);
		}
		if (id[i] == 0)
		{
			if (count == 2 && single_pipe(i, fd))
				return (0);
			if (count > 2 && multi_pipe(i, count ,fd))
				return (0);
			close_pipes(fd, count);
			if (check_out_or_input(pars[i]) == FAILURE)
			{
			//	perror ("fail");
				free_fd_id(fd, id, count);
				free_pars(pars, count);
				exit(EXIT_FAILURE);
			}
			if (pars[i]->cmd != NULL)
				cmd = ft_split(pars[i]->cmd, 32);
			check_make(&cmd[0], env);
			execve(cmd[0], cmd, env);
			perror("Execve error");
			return(0);
		}
		i++;
	}
	close_pipes(fd, count);
	j = 0;
	int status;
	while (j < count)
		waitpid(id[j++], &status, 0);
	free_fd_id(fd, id, count);
	return(1);
}

	

