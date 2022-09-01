/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:47:36 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/01 16:05:53 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_in_file(char *filename, t_pars **pars)
{
	int fd;
	char *file;

	fd = open(filename, O_RDONLY);
	if (fd < 0 && (*pars)->errfile == NULL)
	{
		file = ft_strdup(filename);
		(*pars)->errfile = file;
	}
//	dup2(fd, STDIN_FILENO);
		(*pars)->infilefd = fd;
	return(0);
}

int	open_out_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (1);
	dup2(fd, STDOUT_FILENO);
	return (0);
}

int	opener(char **promt, int j, int i, char c, t_pars **pars)
{
	char	*filename;
	int		boolean;

	boolean = 0;
	filename = ft_trim_substr(promt, j, i);
	if (c == '<')
		boolean = (open_in_file(filename, pars) == 1);
	else if (c == '>')
		boolean = (open_out_file(filename) == 1);
	free(filename);
	return (boolean);
}
