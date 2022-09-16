/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:12:16 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/16 17:58:41 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./Libft/libft.h"
# include <errno.h>
# include <dirent.h>

# define SUCCESS 0
# define FAILURE 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct line
{
	int		pipecount;
	int		infilefd;
	int		outfilefd;
	int		isheredoc;
	int		fileordoc;
	int		app_or_trunc;
	int		errnum;
	char	*errfile;
	char	*cmd;
	char	**infiles;
	char	**outfiles;
	char	**heredocs;
	char	**apendfiles;
	t_env	**env_var;
}	t_pars;

void	do_expand(char	**promt, t_env *env_ , int i);

void	skipquotes(char **promt, int *j);
void	passwords(char **promt, int *i);
int		trimspaces(char	**promt, int *k, char c);
char	*ft_trim_substr(char **source, int start, int end);
void	iffiles(char **promt, int *k);
void	duporjoin(char **line, char **promt, int i, int j);
void	open_in_file(t_pars **pars, char **promt, int j, int i);
void	open_out_file(t_pars **pars, char **promt, int j, int i);
int		check_pipes_count(char **promt, int *count);
int		not_found_second_quote(char *line);
int		openheredoc(char *promt, t_pars **pars);
int		write_docs(char *promt, int count, t_pars **pars);
int		ft_error(char *err_message, int err_code);
int		open_processes(int count, t_pars **pars, char **env, int *status);
int		lexer(char **promt, t_pars ***pars);
int		**make_pipe_for_doc(int count);
int		single_pipe(int i, int (*fd)[2], t_pars *pars);
int		multi_pipe(int i, int count, int (*fd)[2], t_pars *pars);
void	check_make(char **cmd, char **env);
void	free_pars(t_pars **pars, int count);
t_pars	**init_struct(int count, t_env **env);
int		write_in_pipe_and_dup(t_pars **pars, int count, char *delim, int z);
void	skips_and_detect_pipe(char **promt, int *i, int *z);
int		check_redirections(char *promt);


int		only_pipe(char	*promt);
void	free_env(t_env **env);
t_env	*last_env_element(t_env *start);
int		size_of_list(t_env *list);
void	free_after_split(char **store);
int		size_of_env(char **env);
t_env	*env_initialization(char **env);
void	print_environment(t_env *env);
void	remove_from_list(t_env *env, char *key);
char	**list_to_env(t_env	*head);
void	init_pipe(int ***fd_, int count);
int		check_out_or_input(t_pars *pars);
int		close_pipes(int (*fd)[2], int count);
void	free_fd_id(int (*fd)[2], pid_t	*id,  int count);
char	*_getenv(t_env *list, char *key );
char	*get_correct_cmd(char *trash);

#endif
