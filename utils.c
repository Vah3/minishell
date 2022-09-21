/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:37:48 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/21 15:22:42 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_if_does_not_have_quotes(
	char	**line, int expand_or_not, t_pars *pars)
{
	if (expand_or_not == 0)
		do_expand(line, *(pars->env_var), 1);
}

static int	clearquotes(char	**delimetr)
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

int	write_in_pipe_and_dup(t_pars **pars, char *delim, int z)
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
			break ;
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
	if (pars->fileordoc == 0)
	{
		printf("eeeeee\n");
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
