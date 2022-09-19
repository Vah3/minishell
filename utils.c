/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:37:48 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/18 16:11:24 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_if_does_not_have_quotes(
	char	**line, int expand_or_not, t_pars *pars)
{
	t_env	*en;
	int		i;

	i = 0;
	en = *(pars->env_var);
	if (*line && (*(line)[0] == 34 || (*(line)[0] == 39)))
			i = 1;
	if (expand_or_not == 0)
		do_expand(line, *(pars->env_var), i);
}

int	clearquotes(char	**delimetr)
{
	char	*delim;
	char	*newdelim;

	newdelim = NULL;
	delim = *delimetr;
	if (delim && (delim[0] == 34 || delim[0] == 39))
	{
		delim[ft_strlen(delim) - 1] = '\0';
		newdelim = ft_strdup(delim + 1);
		free(delim);
		*delimetr = newdelim;
		return (1);
	}
	return (0);
}

int	write_in_pipe_and_dup(t_pars **pars, int count, char *delim, int z)
{
	int		fd[2];
	char	*line;
	int		expand_or_not;

	if (pipe(fd) == -1)
		return (FAILURE);
	expand_or_not = clearquotes(&delim);
	while (1)
	{
		line = readline(">");
		expand_if_does_not_have_quotes(&line, expand_or_not, pars[0]);
		if (ft_strncmp(delim, line, ft_strlen(line)) == 0)
		{
			count--;
			break ;
		}
		if (write(fd[1], line, ft_strlen(line)) == -1)
			return (FAILURE);
		if (write(fd[1], "\n", 1) == -1)
			return (FAILURE);
	}
	if (close(fd[1]) == -1)
		return (FAILURE);
	pars[z]->isheredoc = dup(fd[0]);
	free(delim);
	return (SUCCESS);
}

void	init_pipe(int ***fd_, int count)
{
	int		(*fd)[2];
	int		i;

	i = 0;
	if (count > 1)
	{
		fd = malloc (sizeof(*fd) * (count - 1));
		if (!fd)
			return ;
	}
	while (i < count - 1)
	{
		if (pipe(fd[i]))
			return ;
		i++;
	}
	*fd_ = (int **)fd;
}

int	check_out_or_input(t_pars *pars)
{
	static int	i;

	i++;
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

int	close_pipes(int (*fd)[2], int count)
{
	int	j;

	j = 0;
	while (j < count - 1)
	{
		if (close(fd[j][0]) == -1)
		{
			perror("CLOSE FAILED");
			return (FAILURE);
		}
		if (close(fd[j][1]) == -1)
		{
			perror("CLOSE FAILED");
			return (FAILURE);
		}
		j++;
	}
	return (SUCCESS);
}
