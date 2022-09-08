/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:44:28 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/08 20:46:18 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_fd_id(int (*fd)[2], pid_t	*id,  int count)
{
	if(count > 1)
		free(fd);
	free(id);
}

int	open_processes(int	count, t_pars **pars, char **env, int *status)
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
			//free_fd_id(fd, id, count);
			//free_pars(pars, count);
		//	return (-1);
		//	exit(EXIT_FAILURE);
			break ;
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
			printf("%s\n", strerror(errno));
			exit(126);
		}
		i++;
	}
	close_pipes(fd, count);
	j = 0;
	while (j < count)
	{
		waitpid(id[j++], status, 0);
		if (WIFEXITED(*status))	
			*status = WEXITSTATUS(*status);	
	/*	else if (WIFSIGNALED(*status))
			*status = WTERMSIG(*status);*/
	}
	free_fd_id(fd, id, count);
	return(1);
}

	

