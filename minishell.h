/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:12:16 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/01 17:05:26 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./Libft/libft.h"

typedef struct line
{
	int		pipecount;
	int		infilefd;
	int		outfilefd;
	int		isheredoc;
	int		apendfile;
	int		fileordoc;
	char	*errfile;
	char	**cmd;
	char	**infiles;
	char	**outfiles;
	char	**heredocs;
	char	**apendfiles;
	char	**envvars;
}	t_pars;

void	skipquotes(char **promt, int *j);
void	passwords(char **promt, int *i);
int		trimspaces(char	**promt, int *k, int *j);
char	*ft_trim_substr(char **source, int start, int end);
void	iffiles(char **promt, int *k, int *n);
void	duporjoin(char **line, char **promt, int i, int j);
int		open_in_files(char *filename, t_pars *pars);
int		open_out_file(char *filename);
int		opener(char **promt, int j, int i, char c, t_pars **pars);
int		check_pipes_count(char **promt, int *count);
int		not_found_second_quote(char *line);
int		openheredoc(char *promt, t_pars **pars);
void	write_docs(char *promt, int count, t_pars **pars);

#endif
