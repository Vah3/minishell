/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:08:16 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/20 20:22:12 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	when_index_is_zero(int (*fd)[2], t_pars *pars)
{
	if (pars->errfile)
	{
		printf("minishell: %s : %s\n",
			pars->errfile, strerror(pars->errnum));
		return (FAILURE);
	}
	if (pars->outfilefd == -1)
		return (FAILURE);
	if (dup2(fd[0][1], 1) == -1)
		return (FAILURE);
	return (SUCCESS);
}

static int	last_pipe(int (*fd)[2], t_pars *pars, int i)
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
	return (SUCCESS);
}

int	single_pipe(int i,int (*fd)[2], t_pars *pars)
{
	if (i == 0 && when_index_is_zero(fd, pars) == FAILURE)
		return (FAILURE);
	if (i == 1)
	{
		if (pars->errfile)
		{
			printf("minishell: %s : %s\n",
				pars->errfile, strerror(pars->errnum));
			return (FAILURE);
		}
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

int	multi_pipe(int i, int (*fd)[2], int count, t_pars *pars)
{
	if (i == 0)
	{
		if (when_index_is_zero(fd, pars) == FAILURE)
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
	else if (i > 0 && last_pipe(fd, pars, i) == FAILURE)
		return (FAILURE);
	check_out_or_input(pars);
	close_pipes(fd, count);
	return (SUCCESS);
}
