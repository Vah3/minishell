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

// int	write_in_pipe_and_dup(t_pars **pars, char *delim, int z)
// {
// 	int		fd[2];
// 	char	*line;
// 	int		expand_or_not;

// 	if (pipe(fd) == -1)
// 		return (FAILURE);
// 	expand_or_not = clearquotes(&delim);
// 	while (1)
// 	{
// 		line = readline(">");
// 		if (!line)
// 		{
// 			// printf("---%s---\n", line);
// 		// printf("%c", 4);
// 			// rl_on_new_line();
// 			// printf("\b");
// 			rl_replace_line("Minishell$", 1);
// 			rl_redisplay();
// 			break;
// 		}
// 		expand_if_does_not_have_quotes(&line, expand_or_not, pars[0]);
// 		if (ft_strncmp(delim, line, ft_strlen(line)) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (write(fd[1], line, ft_strlen(line)) == -1)
// 			return (FAILURE);
// 		free(line);	
// 		if (write(fd[1], "\n", 1) == -1)
// 			return (FAILURE);
// 	}
// 	if (close(fd[1]) == -1)
// 		return (FAILURE);
// 	pars[z]->isheredoc = dup(fd[0]);
// 	free(delim);
// 	return (SUCCESS);
// }

int	init_pipe(int ***fd_, int count)
{
	int		(*fd)[2];
	int		i;

	i = 0;
	fd = NULL;
	if (count > 1)
	{
		fd = malloc (sizeof(*fd) * (count - 1));
		if (!fd)
			return (0);
	}
	while (i < count - 1)
	{
		if (pipe(fd[i]))
			{
				perror("Pipe error");
				return (FAILURE);
			}
		i++;
	}
	*fd_ = (int **)fd;
	return (SUCCESS);
}
//initi return 0-n chpoxel
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
