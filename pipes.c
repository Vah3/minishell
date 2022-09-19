/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:08:16 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/18 15:38:46 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_pipe(int i, int (*fd)[2], t_pars *pars)
{
	if (i == 0)
	{
		if (pars->errfile)
		{
			printf("minishell: %s : %s\n",
				pars->errfile, strerror(pars->errnum));
			return (FAILURE);
		}
		if (pars->outfilefd == -1)
			return (FAILURE);
		if (dup2(fd[i][1], 1) == -1)
			return (1);
	}
	if (i == 1)
	{
		if (pars->errfile)
			return (FAILURE);
		if (pars->outfilefd == -1)
			return (FAILURE);
		if (pars->fileordoc == -1)
			if (dup2(fd[i - 1][0], 0) == -1)
				return (FAILURE);
	}
	check_out_or_input(pars);
	close_pipes(fd, 2);
	return (0);
}

int	multi_pipe(int i, int count, int (*fd)[2], t_pars *pars)
{
	if (i == 0)
	{
		if (pars->errfile)
		{
			printf("minishell: %s : %s\n",
				pars->errfile, strerror(pars->errnum));
			return (FAILURE);
		}
		if (pars->outfilefd == -1)
			return (FAILURE);
		if (dup2(fd[i][1], 1) == -1)
			return (FAILURE);
	}
	else if (i == (count - 1))
	{
		if (pars->errfile)
		{
			printf("minishell: %s : %s\n",
				pars->errfile, strerror(pars->errnum));
			return (FAILURE);
		}
		if (pars->outfilefd == -1)
			return (FAILURE);
		if (dup2(fd[i - 1][0], 0) == -1)
			return (FAILURE);
	}
	else if (i > 0)
	{
		if (pars->errfile)
		{
			printf("minishell: %s : %s\n",
				pars->errfile, strerror(pars->errnum));
			return (FAILURE);
		}
		if (pars->outfilefd == -1)
			return (FAILURE);
		if (dup2(fd[i][1], 1) == -1 || dup2(fd[i - 1][0], 0) == -1)
			return (FAILURE);
	}
	check_out_or_input(pars);
	close_pipes(fd, count);
	return (SUCCESS);
}
