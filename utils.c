/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:37:48 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/12 20:03:11 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_if_does_not_have_quotes(
	char	**line, int expand_or_not, t_pars *pars)
{
	if (expand_or_not == 0)
		do_expand(line, *(pars->env_var), 1);
}

int	clearquotes(char	**delimetr)
{
	char	*delim;
	int		i;

	i = 0;
	delim = *delimetr;
	while (delim && delim[i])
	{
		if (delim[i] == 34 || delim[i] == 39)
		{
			i = -1;
			break ;
		}
		i++;
	}
	*delimetr = get_correct_cmd(*delimetr);
	if (i != -1)
		return (0);
	else
		return (1);
}

int	perror_and_close(int (*fd)[2], int i)
{
	perror("Pipe error");
	while (i > 0)
	{
		i--;
		close(fd[i][0]);
		close(fd[i][1]);
	}
	free(fd);
	return (FAILURE);
}

int	init_pipe(int ***fd_, int count)
{
	int		(*fd)[2];
	int		i;

	i = 0;
	fd = NULL;
	*fd_ = NULL;
	if (count > 1)
	{
		fd = malloc (sizeof(*fd) * (count - 1));
		if (!fd)
			return (FAILURE);
	}
	while (i < count - 1)
	{
		if (pipe(fd[i]))
			return (perror_and_close(fd, i));
		i++;
	}
	*fd_ = (int **)fd;
	return (SUCCESS);
}

int	check_out_or_input(t_pars *pars)
{
	if (pars->fileordoc == 0)
	{
		if (dup2(pars->infilefd, 0) == -1)
			return (FAILURE);
	}
	else if (pars->fileordoc == 1)
	{
		if (dup2(pars->isheredoc, 0) == -1)
			return (FAILURE);
	}
	if (pars->outfilefd > 0)
	{
		if (dup2(pars->outfilefd, 1) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}
