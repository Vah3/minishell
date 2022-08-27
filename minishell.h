/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:12:16 by vagevorg          #+#    #+#             */
/*   Updated: 2022/08/27 20:26:12 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define	MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./Libft/libft.h"

typedef struct line
{
	int		cmdcount;
	int		infile;
	int		outfile;
	int		heredoc;
	int		apendfile;
	int		envvar;
	char	**cmd;
	char	**infiles;
	char	**outfiles;
	char	**heredocs;
	char	**apendfiles;
	char	**envvars;
}	t_pars;

void	skipquotes(char **promt, int *j);
int		trimspaces(char	**promt, int *k, int *j);
char	*ft_trim_substr(char **source, int start, int end);
void	iffiles(char **promt, int *k, int *n);
void	duporjoin(char **line, char **promt, int i, int j);

#endif
