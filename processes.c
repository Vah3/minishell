/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:44:28 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/02 18:01:38 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_processes(int	count, t_pars **pars)
{
	int		i;
	pid_t	*id;
	char **cmd = NULL;

	i = 0;
	id = (pid_t *)malloc(sizeof(pid_t) * count);
	if(!id)
		return (1);
/*	while(i < count)
	{
				printf("%d----%s\n",i, pars[i]->errfile);
				i++;
	}*/
	while(i < count)
	{
		id[i] = fork();
		if(id[i] == -1)
			return (1);
		if(id[i] == 0)
		{
			if(pars[i]->errfile)
			{
				printf("%s: No such file or directory\n", pars[i]->errfile);
				return (0);
			}
			if(pars[i]->fileordoc == 0)
			{
				if(dup2(pars[i]->infilefd, 0) == -1)
					return (0);
			}
			else if (pars[i]->fileordoc == 1)
			{
				if(dup2(pars[i]->isheredoc, 0) == -1)
					return (0);
			}
			if (pars[i]->cmd != NULL)
				cmd = ft_split(pars[i]->cmd, 32);
			execve(cmd[0], cmd, NULL);
		//	printf("%s----%d\n",pars[i]->cmd ,i);
			return(0);
		//	printf("%s----%d\n",pars[i]->cmd ,id[i]);
		}
		i++;
	}
	return(0);
}

		
	

