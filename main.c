/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:43:13 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/25 09:46:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <unistd.h>

int 	status = 0;


void	handle(int i)
{
	// rl_
	(void) i;
	status = 1;
	 write(1, "\n", 1);
	 rl_on_new_line();
	 rl_replace_line("", 0);
	 rl_redisplay();
}
void	handle1(int i)
{
	// rl_
	(void) i;
	status = 1;
	 rl_on_new_line();
	 rl_replace_line("", 0);
	 //rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
//	static int a = 0;
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
	while(1)
	{
		tcgetattr(0, &termios_p);
		termios_p.c_lflag &= ~ECHOCTL;
		tcsetattr(0, 0, &termios_p);
		signal(SIGINT, handle);
		promt = readline("Minishell$ ");
		signal(SIGINT, handle1);
		env = list_to_env(env_, status);
		if (!promt)
		{
			free_after_split(env);
			free_env_(&env_);
			termios_p.c_lflag |= ECHOCTL;
			tcsetattr(0, 0, &termios_p);
			return (0);
		}
		if (!promt[0])
			continue;
		add_history(promt);
		 if (not_found_second_quote(promt) || only_pipe(promt))
		 	continue ;
		if(check_redirections(promt))
		{
			status = 258;
			free (promt);
			continue ;
		}
		if (check_pipes_count(&promt, &count))
		{
			return(ft_error("Pipe error\n", 1));
		}
		pars = init_struct(count, &env_);
		if(!pars)
			return (0);
		if(openheredoc(promt, pars)) // heredocery stexic a bacum
		{
			free_pars(pars, count);
			free(promt);
			continue ;
		}
		do_expand(&promt, env_, 0); ///////expand
		if (lexer(&promt, &pars))
		{
			 free_pars(pars, count);
			 free(promt);
			continue ;
		}
		open_processes(count, pars, env, &status);	
		free(promt);
		free_after_split(env);
		termios_p.c_lflag |= ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}
	return (0);
}

