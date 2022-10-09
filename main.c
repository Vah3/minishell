/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:43:13 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/09 18:49:41 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <unistd.h>

int 	status = 0;

void	set_term_attr(int on_off)
{
	struct termios termios_p;

	tcgetattr(0, &termios_p);
	if (on_off == 0)
	{
		termios_p.c_lflag &= ~ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}
	else if (on_off == 1)
	{
		termios_p.c_lflag |= ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}
		
}

void	save_std(void)
{
	static int stdin_;
	static int stdout_;
	static int	count;

	if (count == 0)
	{
		stdin_ = dup(STDIN_FILENO);
		stdout_ = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(stdin_, STDIN_FILENO);
		dup2(stdout_, STDOUT_FILENO);		
	}
	count++;
}

void	set_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

int	free_everything(t_pars **pars, char *promt, char **env)
{
	free_pars(pars);
	free(promt);
	free_after_split (env);
	return (1);
}
int	simple_built_in(t_pars **pars, t_env *env_, char ***env)
{
	if (there_is_builtin(pars[0]->cmd))	
	{
		*env = change_under_score(env_, pars[0]->cmd, *env);
		if (pars[0]->errfile)
		{
			printf("minishell: %s : %s\n",
				pars[0]->errfile, strerror(pars[0]->errnum));
				return (1);
		}
		if (pars[0]->outfilefd == -1)
			return (1);
		check_out_or_input(pars[0]);
		call_builtin(pars, pars[0]->cmd, there_is_builtin(pars[0]->cmd), env_); 
		save_std();
		return (1);
	}
return (0);
}

void	free_and_exit(t_env *env_, char **env)
{
	printf("exit\n");
	free_after_split(env);
	free_env_(&env_);
	set_term_attr(1);
	exit (status);
}

int	some_checks(char *promt, t_env *env_, char **env, int *count)
{
	signal(SIGINT, handle1);
	if (!promt)
		free_and_exit(env_, env);
	if ((!promt || promt[0] == '\0') && free_everything(NULL, promt, env))
		return (1);
	add_history(promt);
	if ((not_found_second_quote(promt) || only_pipe(promt) || check_redirections(promt) || check_pipes_count(&promt, count)) && free_everything(NULL, promt, env))
	 	return (1);
	return (0);
}

int	some_stuff(char **promt, t_env *env_ ,t_pars **pars, int *gr)
{
	if(openheredoc(*promt, pars))
	{
		*gr = 1;
		signal(SIGINT, handle4);
		return (1) ;
	}
	do_expand(promt, env_, 0);
	if (lexer(promt, pars))
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int 	gr;
	char	*promt;
	t_pars	**pars;
	int		count;
	t_env	*env_;

	(void)argc;
	(void)argv;
	gr = 0;
	set_signal();
	env_ = env_initialization(env);
	save_std();
	while(1)
	{
		save_std();
		set_term_attr(0);
		if (gr == 0)
			signal(SIGINT, handle0);
		promt = readline("Minishell$ ");
		env = list_to_env(env_);
		if (some_checks(promt, env_, env, &count))
			continue ;
		pars = init_struct(count, &env_);
		if (some_stuff(&promt, env_, pars, &gr) && free_everything(pars, promt, env))
			continue;
		if (count == 1 && simple_built_in(pars, env_, &env) && free_everything(pars, promt, env))
			continue;
		env = change_under_score(env_, promt, env);
		open_processes(count, pars, env, env_);
		free_everything(NULL, promt, env);
		gr = 0;
	}
	return (0);
}

