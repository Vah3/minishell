/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:47:36 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/18 15:32:51 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_in_file(t_pars **pars, char **promt, int j, int i)
{
	int		fd;
	char	*file;
	char	*filename;

	filename = ft_trim_substr(promt, j, i);
	fd = open(filename, O_RDONLY);
	(*pars)->fileordoc = 0;
	if (fd < 0 && (*pars)->errfile == NULL)
	{
		file = ft_strdup(filename);
		(*pars)->errnum = errno;
		if (!file)
		{	
			perror ("malloc failed");
			exit(FAILURE);
		}
		(*pars)->errfile = file;
	}
	(*pars)->infilefd = fd;
	free(filename);
}

void	open_out_file(t_pars **pars, char **promt, int j, int i)
{
	int		fd;
	char	*filename;

	filename = ft_trim_substr(promt, j, i);
	fd = -1;
	if ((*pars)->errfile == NULL)
	{
		if ((*pars)->app_or_trunc == 1)
			fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if ((*pars)->app_or_trunc == 0)
			fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if ((*pars)->outfilefd > -1)
			(*pars)->outfilefd = fd;
	}
	free(filename);
}
