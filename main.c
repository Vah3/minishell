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

int	main(int argc, char **argv, char **env)
{
//	static int a = 0;
	char	*promt;
	t_pars	**pars;
	int 	status = 0;
	int		count;
	(void)argc;
	(void)argv;
	t_env	*env_;

	env_ = env_initialization(env);
	while(1)
	{
	env = list_to_env(env_, status);

	promt = readline("Minishell$ ");
	if (!promt)
	{
		free_after_split(env);
		free_env_(&env_);
		return (0);
	}
	if (!promt[0])
		continue;
	add_history(promt);
	 if (not_found_second_quote(promt) || only_pipe(promt))
	 	continue ;
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
	if(check_redirections(promt))
	{
		status = 258;
		 free_pars(pars, count);
		 free (promt);
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
}
	return (0);
}

