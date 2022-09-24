/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:12:16 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/21 15:22:14 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*			HEADER	FILES			*/
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
/*			HEADER	FILES			*/

# define SUCCESS 0
# define FAILURE 1

/*			ENV		LIST			*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;
/*/////////////////////////////////// */

/*			T_PARS					*/
typedef struct s_pars
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
	char	**exec_cmd;
	t_env	**env_var;
}	t_pars;
/*////////////////////////////////////// */

/*						CHECK.C		5					  	     */
int		check_redirections(char *promt);
int		not_found_second_quote(char *line);
int		only_pipe(char	*promt);
/*/////////////////////////////////////////////////////////////// */

/*						COUNTPIPE.C	5					     */
int		check_pipes_count(char **promt, int *count);
void	free_pars(t_pars **pars, int count);
char	*ft_trim_substr(char **source, int start, int end);
/*/////////////////////////////////////////////////////////////// */

/*						EXPAND.C	4						     */
void	update_status(t_env *env, int status);
void	do_expand(char **promt, t_env *env_, int doc);
/*//////////////////////////////////////////////////////////////// */

/*						GET_CORRECT_CMD.C	3			   	     */
char	*get_correct_cmd(char *trash);
/*//////////////////////////////////////////////////////////////// */

/*						GET_ENV_LIST.C	5			   	     */
t_env	*env_initialization(char **env);
void	print_environment(t_env *env);
void	remove_from_list(t_env *env, char *key);
/*//////////////////////////////////////////////////////////////// */

/*						GET_ENV_UTILS.C	 5			   	     */
void	free_env(t_env **env);
t_env	*last_env_element(t_env *start);
int		size_of_list(t_env *list);
void	free_after_split(char **store);
int		size_of_env(char **env);
/*//////////////////////////////////////////////////////////////// */

/*						GET_ENV_UTILS1.C	3			   	     */
char	**list_to_env(t_env	*head, int status);
void	env_replace(t_env *env, char *key, char *value);
char	*_getenv(t_env *list, char *key );
/*//////////////////////////////////////////////////////////////// */

/*						INIT_STRUCT.C	2			   	     */
t_pars	**init_struct(int count, t_env **env);
/*//////////////////////////////////////////////////////////////// */

/*						OPEN_DOCS.C				   	     */
int		openheredoc(char *promt, t_pars **pars);
void	skips_and_detect_pipe(char **promt, int *i, int *z);
int		write_docs(char *promt, t_pars **pars);

/*//////////////////////////////////////////////////////////////// */

/*						OPEN_FILES.C				   	     */
void	open_in_file(t_pars **pars, char **promt, int j, int i);
void	open_out_file(t_pars **pars, char **promt, int j, int i);
/*//////////////////////////////////////////////////////////////// */

/*						PARSUTILS.C				   	     */
void	skipquotes(char **promt, int *j);
int		trimspaces(char	**promt, int *k, char c);
void	iffiles(char **promt, int *k);
void	skip_slesh_quote_1(char *promt, int *i, int *count);
/*//////////////////////////////////////////////////////////////// */

/*						PIPES.C				   	     */
int		single_pipe(int i, int (*fd)[2], t_pars *pars);
int		multi_pipe(int i, int (*fd)[2], int count, t_pars *pars);
/*//////////////////////////////////////////////////////////////// */

/*						PIPEX.C				   	     */
void	check_make(char **cmd, char **env);
/*//////////////////////////////////////////////////////////////// */

/*						PROCESSES.C				   	     */
int		close_pipes(int (*fd)[2], int count);
void	open_processes(int count, t_pars **pars, char **env, int *status);
/*//////////////////////////////////////////////////////////////// */

/*						UTILS_FOR_NORM_PROC.C				   	     */
void	free_fd_id(int (*fd)[2], pid_t	*id, int count);
int		fr(t_pars **pars, int (*fd)[2], pid_t *id, int count);
int		make_cmd(t_pars *pars, char **env);
void	without_pipes(t_pars **pars, int (*fd)[2], pid_t *id, int count);
void	wait_(int *status, int (*fd)[2], pid_t *id, int count);
/*//////////////////////////////////////////////////////////////// */

/*						REDIRECTIONS.C	5			   	     */
int		lexer(char **promt, t_pars ***pars, char **env);
/*//////////////////////////////////////////////////////////////// */

/*						UTILS.C				   	     */
int		write_in_pipe_and_dup(t_pars **pars, char *delim, int z);
void	init_pipe(int ***fd_, int count);
int		check_out_or_input(t_pars *pars);

/*//////////////////////////////////////////////////////////////// */
int		ft_error(char *err_message, int err_code);
int	correct_delim(char *promt, int i);



#endif
