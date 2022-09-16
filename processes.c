/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:44:28 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/16 19:00:55 by vagevorg         ###   ########.fr       */
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
	while (i < count)
	{
		id[i] = fork();
		if (id[i] == -1)
		{
			perror("forks failed");
			break ;
		}
		if (id[i] == 0)
		{
			if (pars[i]->cmd != NULL)// && check_out_or_input(pars[i]) != FAILURE )
			{
				cmd = ft_split(pars[i]->cmd, 32);
				check_make(&cmd[0], env);
			}
			if (count == 2 && single_pipe(i, fd, pars[i]))   //check anoxy utilsnerum a
				exit (EXIT_FAILURE);
			if (count > 2 && multi_pipe(i, count ,fd, pars[i]))
				exit (EXIT_FAILURE);
			else if (count == 1)
			{
		//	close_pipes(fd, count);
			if (pars[i]->errfile)
				printf("minishell: %s : %s\n", pars[i]->errfile, strerror(pars[i]->errnum));
			if (pars[i]->outfilefd == -1)
				;
			if (check_out_or_input(pars[i]) == FAILURE)
			{
//				if(pars[i]->errfile && printf("minishell: %s : %s\n", pars[i]->errfile, strerror(pars[i]->errnum)))
//				;
				free_fd_id(fd, id, count);
				free_pars(pars, count);
				exit(EXIT_FAILURE);
			}
			}
/*			if (pars[i]->cmd != NULL)
				cmd = ft_split(pars[i]->cmd, 32);
			check_make(&cmd[0], env);*/
			execve(cmd[0], cmd, env);
			if ( ft_strlen(pars[i]->cmd) == 0)
				exit(0);
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
	return(SUCCESS);
}

	

