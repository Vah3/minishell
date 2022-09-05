/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:44:28 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/05 10:43:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void free_fd_id(int (*fd)[2], pid_t	*id,  int count)
{
	int	j;

	j = 0;
	while (j < count - 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
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
	char **cmd = NULL;

	i = 0;
	if (count > 1)
		fd = malloc (sizeof(*fd) * (count - 1));
	while (i < count - 1)
	{
		if (pipe(fd[i]))
			return (0);
		i++;
	}
	i = 0;
	id = (pid_t *)malloc(sizeof(pid_t) * count);
	if (!id)
		return (1);	
	while (i < count)
	{
		id[i] = fork();
		if (id[i] == -1)
			return (1);
		if (id[i] == 0)
		{
			if (count == 2 && single_pipe(i, fd))
				return (0);
			if (count > 2 && multi_pipe(i, count ,fd))
				return (0);
			if (pars[i]->errfile || pars[i]->outfilefd == -1)
			{
				free_fd_id(fd, id, count);
				free_pars(pars, count);
				exit(0);
			}
			while ( j < count - 1)
			{
				close(fd[j][0]);
				close(fd[j][1]);
				j++;
			}
			if (pars[i]->fileordoc == 0)
			{
				if(dup2(pars[i]->infilefd, 0) == -1)
					return (0);
			}
			else if (pars[i]->fileordoc == 1)
			{
				if (dup2(pars[i]->isheredoc, 0) == -1)
					return (0);
			}
			if (pars[i]->outfilefd > 0)
			{
				if (dup2(pars[i]->outfilefd, 1) == -1)
					return (0);
			}
			if (pars[i]->cmd != NULL)
				cmd = ft_split(pars[i]->cmd, 32);
			check_make(&cmd[0], env);
			execve(cmd[0], cmd, env);
			perror("");
		//	printf("%s----%d\n",pars[i]->cmd ,i);
			return(0);
		//	printf("%s----%d\n",pars[i]->cmd ,id[i]);
		}
		i++;
	}

 	// j = 0;
	// while (j < count - 1)
	// {
	// 	close(fd[j][0]);
	// 	close(fd[j][1]);
	// 	j++;
	// }
	
	// j = 0;
	// int status;
	// while (j < count)
	// {
	// 	waitpid(id[j], &status, 0);
	// 	j++;
	// }
	free_fd_id(fd, id, count);
	// j = 0;
	// while (j < count - 1)
	// {
	// 	free(fd[j++]);
	// }
	
	// free(id);
	
	
	return(1);
}

	

