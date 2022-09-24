/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:43:13 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/24 14:53:23 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*promt;
	t_pars	**pars;
	int		i;
	int 	status = 0;
	int		count;
	(void)argc;
	(void)argv;
	t_env	*env_;
	env_ = env_initialization(env);

	while(1)
	{
	i = 0;
	env = list_to_env(env_, status);
	promt = readline("Minishell$ ");
	if (!promt)
		return (0);
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
	if (lexer(&promt, &pars, env))
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

