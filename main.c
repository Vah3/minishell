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

int	checking_line(char *line, char *delim)
{
	if(status == -1)
		return (1);
	if (!line)
	{
		rl_replace_line("Minishell$", 1);
		rl_redisplay();
		return (1);
	}
	if (ft_strncmp(delim, line, ft_strlen(line)) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	set_status_back(int input_fd)
{
	if (status == -1)
	{
		status = 1;
		dup2(input_fd, 0);
		signal(SIGINT, handle4);
		return (1);
	}
	return (0);
}
int	close_pipe_and_free_delim(int fd[2], int z, t_pars **pars, char *delim)
{
	if (close(fd[1]) == -1)
		return (FAILURE);
	pars[z]->isheredoc = dup(fd[0]);
	free(delim);
	return (0);
}
int	write_in_pipe_and_dup(t_pars **pars, char *delim, int z)
{
	int		fd[2];
	char	*line;
	int		expand_or_not;
	int		input;

	if (pipe(fd) == -1)
		return (FAILURE);
	expand_or_not = clearquotes(&delim);
	input = dup(0);
	signal(SIGINT, handle2);
	while (1)
	{
		line = readline(">");
		expand_if_does_not_have_quotes(&line, expand_or_not, pars[0]);
		if (checking_line(line, delim))
			break ;
		if (write(fd[1], line, ft_strlen(line)) == -1)
			return (FAILURE);
		if (write(fd[1], "\n", 1) == -1)
			return (FAILURE);
		free(line);
	}
	if(close_pipe_and_free_delim(fd, z, pars, delim) == FAILURE
		|| set_status_back(input))
		return (FAILURE);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
//	static int  a = 0;
	int 	gr = 0;
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
		if (gr == 0)
			signal(SIGINT, handle0);
		promt = readline("Minishell$ ");
		signal(SIGINT, handle1);
		if (!promt)
		{
			//free_after_split(env);
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
			gr = 1;
			free_pars(pars, count);
			free(promt);
			signal(SIGINT, handle4);
		//	env = list_to_env(env_, status);
			continue ;
		}
		do_expand(&promt, env_, 0); ///////expand
		env = list_to_env(env_, status, promt);
		if (promt && lexer(&promt, &pars))
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
		gr = 0;
	}
	return (0);
}

