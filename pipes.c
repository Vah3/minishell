/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:08:16 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/04 15:27:15 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_pipe(int i, int (*fd)[2])
{
	if (i == 0)
		if (dup2(fd[i][1], 1) == -1)
			return (1);
	if (i == 1)
		if (dup2(fd[i - 1][0], 0) == -1)
			return (1);
	return (0);
}

int	multi_pipe(int i, int count, int (*fd)[2])
{
	if (i == 0)
	{
		if (dup2(fd[i][1], 1) == -1)
			return (1);
	}
	else if (i == (count - 1))
	{
		if (dup2(fd[i - 1][0], 0) == -1)
			return (1);
	}
	else if (i > 0)
	{
		if (dup2(fd[i][1], 1) == -1 || dup2(fd[i - 1][0], 0) == -1)
			return (1);
	}
	return (0);
}
