/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:43:13 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/08 18:40:29 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <unistd.h>

int 	status = 0;



int	main(int argc, char **argv, char **env)
{
//	static int  a = 0;
	int 	gr = 0;
	int		stdin_, stdout_;
	char	*promt;
	t_pars	**pars;
	int		count;
	(void)argc;
	(void)argv;
	t_env	*env_;
	struct termios termios_p;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	env_ = env_initialization(env);
	stdin_ = dup(STDIN_FILENO);
	stdout_ = dup(STDOUT_FILENO);
	while(1)
	{
		tcgetattr(0, &termios_p);
		termios_p.c_lflag &= ~ECHOCTL;
		tcsetattr(0, 0, &termios_p);
		if (gr == 0)
			signal(SIGINT, handle0);
		promt = readline("Minishell$ ");
		env = list_to_env(env_);
		signal(SIGINT, handle1);
		if (!promt)
		{
			printf("exit\n");
			free_after_split(env);
			free_env_(&env_);
			termios_p.c_lflag |= ECHOCTL;
			tcsetattr(0, 0, &termios_p);
			return (status);
		}
		if (!promt || promt[0] == '\0')
		{
			free(promt);
			free_after_split(env);
			continue;
		}
		add_history(promt);
		 if (not_found_second_quote(promt) || only_pipe(promt))
		 {
			free(promt);
			free_after_split(env);
		 	continue ;
		 }
		if(check_redirections(promt))
		{
			free (promt);
			free_after_split (env);
			continue ;
		}
		if (check_pipes_count(&promt, &count))
		{
			free(promt);
			free_after_split(env);
		 	continue ;
		}
		pars = init_struct(count, &env_);
		//if(!pars)
		//	return (0);
		if(openheredoc(promt, pars))// || !promt) // heredocery stexic a bacum
		{
			gr = 1;
			free_pars(pars);
			free(promt);
			free_after_split (env);
			signal(SIGINT, handle4);
		//	env = list_to_env(env_, status);
			continue ;
		}
		do_expand(&promt, env_, 0); ///////expand
		if (lexer(&promt, pars))
		{
			free_pars(pars);
			free(promt);
			free_after_split (env);
			continue ;
		}
		if (count == 1 && there_is_builtin(pars[0]->cmd))//<-----------------------
		{
			env = change_under_score(env_, pars[0]->cmd, env);
			if (pars[0]->errfile)
			{
				printf("minishell: %s : %s\n",
					pars[0]->errfile, strerror(pars[0]->errnum));
				free_pars(pars);
				free(promt);
				free_after_split(env);
				continue;
			}
			if (pars[0]->outfilefd == -1)
			{
				free_pars(pars);
				free(promt);
				free_after_split(env);
				continue ;
			}
			check_out_or_input(pars[0]);
			call_builtin(pars, pars[0]->cmd, there_is_builtin(pars[0]->cmd), env_); 
			free_pars(pars);
			free(promt);
			free_after_split(env);
			dup2(stdin_, STDIN_FILENO);
			dup2(stdout_, STDOUT_FILENO);
			continue;
		}
		env = change_under_score(env_, promt, env);
		open_processes(count, pars, env, env_);
		free(promt);
		free_after_split(env);
		termios_p.c_lflag |= ECHOCTL;
		tcsetattr(0, 0, &termios_p);
		gr = 0;
	}
	return (0);
}

