/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_norm_proc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:21:20 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/21 14:22:52 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int status;
void	free_fd_id(int (*fd)[2], pid_t *id, int count)
{
	if (count > 1)
		free(fd);
	free(id);
}

int	fr(t_pars **pars, int (*fd)[2], pid_t *id, int count)
{
	free_fd_id(fd, id, count);
	free_pars(pars, count);
	return (1);
}

int	make_cmd(t_pars *pars, char **env)
{
	char	**command;
	int		j;

	j = 0;
	command = NULL;
	if (pars->cmd != NULL && pars->errfile == NULL)
	{
		command = ft_split(pars->cmd, 32);
		if (!command )
			return (FAILURE);
		while (command[j])
		{
			command[j] = get_correct_cmd(command[j]);
			j++;
		}
		check_make(&command[0], env);
		pars->exec_cmd = command;
	}
	return (SUCCESS);
}

void	without_pipes(t_pars **pars, int (*fd)[2], pid_t *id, int count)
{
	if (pars[0]->errfile)
	{
		printf("minishell: %s : %s\n",
			pars[0]->errfile, strerror(pars[0]->errnum));
		fr(pars, fd, id, count);
		exit(EXIT_FAILURE);
	}
	if (pars[0]->outfilefd == -1 && fr(pars, fd, id, count))
		exit(EXIT_FAILURE);
	if (check_out_or_input(pars[0]) == FAILURE
		&& fr(pars, fd, id, count))
		exit(EXIT_FAILURE);
}

void	wait_(int (*fd)[2], pid_t *id, int count)
{
	int	j;

	j = 0;
	close_pipes(fd, count);
	while (j < count)
	{
		waitpid(id[j++], &status, 0);
		if (j == count && WIFEXITED (status))
			status = WEXITSTATUS(status);
		else if(j == count && WIFSIGNALED(status))
		{
			status = WTERMSIG(status) + 128;
			 write(1, "\n", 1);
		}
	}
}
