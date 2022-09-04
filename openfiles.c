/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:47:36 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/04 19:41:10 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	/*dup2(fd, STDIN_FILENO);*/
int	open_in_file(char *filename, t_pars **pars)
{
	int		fd;
	char	*file;

	fd = open(filename, O_RDONLY);
	if (fd < 0 && (*pars)->errfile == NULL)
	{
		file = ft_strdup(filename);
		(*pars)->errfile = file;
	}
	(*pars)->infilefd = fd;
	return (0);
}

int	open_out_file(char *filename, t_pars **pars, char c)
{
	int	fd;
	
	fd = -1;
	if (c == '>')
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (c == 'a')
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if((*pars)->outfilefd > -1)
		(*pars)->outfilefd = fd;
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
		boolean = (open_out_file(filename, pars, c) == 1);
	free(filename);
	return (boolean);
}
