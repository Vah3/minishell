/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:43:13 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/15 20:07:16 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_pars(t_pars **pars, int count)
{
	int	i;
	i = 0;
	/*						FREE PARS					*/
	while (i < count)
	{
		free(pars[i]->cmd);
		if (pars[i]->errfile)
			free(pars[i]->errfile);
		free(pars[i]);
		i++;
	}
	free(pars);
}

char	*ft_trim_substr(char **source, int start, int end)
{
	char	*ret_string;
	char	*new_string;
	int		i;

	ret_string = ft_substr(*source, start, end - start);
	new_string = malloc(sizeof(char) * (
				ft_strlen(*source) - (end - start) + 1));
	i = -1;
	while ((*source)[++i] && i < start)
		new_string[i] = (*source)[i];
	while ((*source)[end] && end < (int)ft_strlen(*source))
		new_string[i++] = (*source)[end++];
	new_string[i] = '\0';
	free(*source);
	*source = new_string;
	return (ret_string);
}

void	passwords(char **promt,  int *i)
{
	if((*promt)[*i] && ((*promt)[*i] != '<' && (*promt)[*i] != '>' && (*promt)[*i] != '|'))
	{
		while((*promt)[*i] && (*promt)[*i] != 32)
			(*i)++;
	}
}

void	if_dollar_question_mark(char **promt, int status)
{
	char	*line;
	char	*before;
	char	*after;
	char	*char_stat;

	line = ft_strnstr (*promt, "$?", ft_strlen(*promt));
	while (line)
	{
		after = ft_strdup(line + 2);
		*line = '\0';
		before = ft_strdup(*promt);
		free(*promt);
		char_stat = ft_itoa(status);
		*promt = ft_strjoin(before, char_stat);
		free(char_stat);
		*promt = ft_strjoin (*promt, after);
		free (after);
		line = ft_strnstr (*promt, "$?", ft_strlen(*promt));
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*promt;
	t_pars	**pars;
	int		i;
	int 	status = 0;
	int		count;
	char	**cmd;
	(void)argc;
	(void)argv;
	t_env	*env_;

	env_ = env_initialization(env);

	while(1)
	{
	i = 0;
	env = list_to_env(env_);
	promt = readline("Minishell ");
	if (!promt )
		return (0);
	add_history(promt);
	 if (ft_strlen(promt) == 0 || not_found_second_quote(promt) || only_pipe(promt))
	 	continue ;
	if (check_pipes_count(&promt, &count))
	{
		printf("Pipe count--->%d\n", count);
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
	if_dollar_question_mark(&promt, status);
	do_expand(&promt, env_); ///////expand
	if (lexer(&promt, &pars))
	{
		free_pars(pars, count);
		free(promt);
		continue ;
	}
	cmd = ft_split(promt, '|');
	if (count < 2)
		pars[i]->cmd = ft_strdup(promt);
	else
	{
		while(i < count)
		{
			pars[i]->cmd = ft_strdup(cmd[i]);
			i++;
		}
	}
	free_after_split(cmd);
	cmd = NULL;
	if (/*ft_strlen(promt) != 0 &&*/ open_processes(count, pars, env, &status) == FAILURE)
		free_pars(pars, count);
	free_pars(pars, count);
	free(promt);
	free(env);
}

	return (0);
}

