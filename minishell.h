/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:12:16 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/12 20:42:53 by vagevorg         ###   ########.fr       */
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
# include <signal.h>
# include <termios.h>
# include <limits.h>
/*			HEADER	FILES			*/

# define SUCCESS 0
# define FAILURE 1

# define IS_ECHO		2
# define IS_CD			3	
# define IS_PWD			4
# define IS_EXPORT		5
# define IS_UNSET		6
# define IS_ENV			7
# define IS_EXIT		8

# define JOIN_MODE		0
# define ADD_MODE		1

/*			ENV		LIST			*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_export
{
	char	**splited_prompt;
	char	*key;
	char	*value;
	int		mode;
}	t_export;
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
void	free_pars(t_pars **pars);
char	*ft_trim_substr(char **source, int start, int end);
/*/////////////////////////////////////////////////////////////// */

/*						EXPAND.C	4						     */
void	update_status(t_env *env);
void	do_expand(char **promt, t_env *env_, int doc);
/*//////////////////////////////////////////////////////////////// */

/*						GET_CORRECT_CMD.C	3			   	     */
char	*get_correct_cmd(char *trash);
/*//////////////////////////////////////////////////////////////// */

/*						GET_ENV_LIST.C	5			   	     */
t_env	*env_initialization(char **env);
void	print_environment(t_env *env);
void	remove_from_list(t_env *env, char *key);
void	env_add_back(t_env **list, t_env *new_item);
t_env	*new_env_element(char *key, char *value);
int		key_len(char *s);
/*//////////////////////////////////////////////////////////////// */

/*						GET_ENV_UTILS.C	 5			   	     */
//void	free_env(t_env **env);
t_env	*last_env_element(t_env *start);
int		size_of_list(t_env *list);
void	free_after_split(char **store);
int		size_of_env(char **env);
void	free_env_(t_env **env);
/*//////////////////////////////////////////////////////////////// */

/*						GET_ENV_UTILS1.C	3			   	     */
char	**list_to_env(t_env	*head);
void	env_replace(t_env *env, char *key, char *value);
/*//////////////////////////////////////////////////////////////// */

/*						INIT_STRUCT.C	2			   	     */
t_pars	**init_struct(int count, t_env **env);
/*//////////////////////////////////////////////////////////////// */

/*						OPEN_DOCS.C				   	     */
int		openheredoc(char *promt, t_pars **pars);
void	skips_and_detect_pipe(char **promt, int *i, int *z);
int		write_docs(char *promt, t_pars **pars);
void	process_redirections(char *promt, int *i, int *j);

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
void	skip_slesh_quote_2(char *promt, int *i, int *len);
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
void	open_processes(int count, t_pars **pars, char **env, t_env *env_);
/*//////////////////////////////////////////////////////////////// */

/*						UTILS_FOR_NORM_PROC.C				   	     */
void	free_fd_id(int (*fd)[2], pid_t	*id, int count);
int		fr(t_pars **pars, int (*fd)[2], pid_t *id, int count);
int		make_cmd(t_pars *pars, char **env);
void	without_pipes(t_pars **pars, int (*fd)[2], pid_t *id, int count);
void	wait_(int (*fd)[2], pid_t *id, int count);
/*//////////////////////////////////////////////////////////////// */

/*						REDIRECTIONS.C	5			   	     */
int		lexer(char **promt, t_pars **pars);
int		if_in_file(char **promt, t_pars **pars, int *i, int *z);
int		if_out_file(char **promt, t_pars **pars, int *i, int *z);
int		if_here_doc(char **promt, int *fileordoc, int *i, int *z);
int		if_append_file(char **promt, t_pars **pars, int *i, int *z);
/*//////////////////////////////////////////////////////////////// */

/*						UTILS.C				   	     */
int		write_in_pipe_and_dup(t_pars **pars, char *delim, int z);
int		init_pipe(int ***fd_, int count);
int		check_out_or_input(t_pars *pars);
int		clearquotes(char	**delimetr);
void	expand_if_does_not_have_quotes(
			char	**line, int expand_or_not, t_pars *pars);

/*//////////////////////////////////////////////////////////////// */
int		ft_error(char *err_message, int err_code);
int		correct_delim(char *promt, int i);

/*						BUILTIN_EXPORT.C				   	     */
void	skip_spaces(char *str, int *i);
int		there_is_builtin(char *str);
int		call_builtin(t_pars *pars, char *prompt, int id, t_env *env);

int		call_export(char *prompt, t_env *env);
int		call_env(t_env *env);
int		call_unset(char *prompt, t_env *env);
int		call_echo(char *prompt);
int		call_cd(char *prompt, t_env *env);
int		call_pwd(t_env *list);
int		call_exit(t_pars *pars, char *line);

int		exists_key(char *key, t_env *env);
void	update_value(t_env **env, char *key, char *value);
void	update_value_cd(t_env **env, char *key, char *value);
int		is_valid_key(char *key);

int		set_status_back(int input_fd);
void	handle4(int i);
void	handle2(int i);
void	handle1(int i);
void	handle0(int i);
char	**change_under_score(t_env *env_list, char *promt, char **env);
void	clear_spaces_if_all_are_spaces(char **line);
int		close_pipe_and_free_delim(int fd[2], int z, t_pars **pars, char *delim);
int		checking_line(char *line, char *delim);
char	*change_delim_key(char *delim);

//exit_utils.c
int		ft_string_isdigit(char *str);
int		non_numeric(char *str);
void	exiting(int count_of_args, int code);
char	*_getenv(t_env *list, char *key );

//ft_export_utils1.c
void	update_key_values(char *key, char *value, t_env *env);
void	join_and_free(t_env **env, char **key, char **value, int *i);
void	get_correct_key_value(char *str, int mode, char **key, char **value);
char	*get_key(int mode, char *arg);
void	print_export_err_and_ch_s(char *str, int *i);

//ft_export_utils2.c
void	update_value_cd(t_env **env, char *key, char *value);
void	join_value(t_env **env, char *key, char *value);
int		is_valid(char *str, int *mode);
int		print_export(t_env *env, char **splited_prompt);
void	update_and_add(t_env *env, char *key, char *value);

//get_env_list_utils.c
int		set_lvl(t_env *env, int *lvl);
void	set_shlvl(t_env *env);
void	set_def_env(char **env_, t_env **env_list);
void	set_pwd_oldpwd(t_env *env, char *cur_pwd);
void	set_additional_pwd_oldpwd(t_env *env, char *cur_pwd);
char	*set_back_slesh(char *line);

//opendocs_utils.c
int		ft_error(char *err_message, int err_code);
int		correct_delim(char *promt, int i);
void	skips_and_detect_pipe(char **promt, int *i, int *z);
void	process_redirections(char *promt, int *i, int *j);
int		close_pipe_and_free_delim(int fd[2], int z, t_pars **pars, char *delim);

//processes_utils.c
void	print_in_errno_and_free_exit(
			char **command, int code, char **cmd, t_env *env);
int		malloc_and_check(int count, int ***fd_, t_pars **pars, pid_t **id_);
int		free_and_close(int (*fd)[2], int count, t_pars **pars, pid_t *id);
void	clear_spaces_if_all_are_spaces(char **line);
int		do_parsing(char **line, t_pars **pars);

//utils_main.c
void	set_setting(int gr);
int		fret(t_pars **pars, char *promt, char **env);
void	set_signal(void);
void	save_std(void);
void	set_term_attr(int on_off);

//utils_main1.c
void	free_and_exit(t_env *env_, char **env);
int		free_and_close(int (*fd)[2], int count, t_pars **pars, pid_t *id);

#endif
