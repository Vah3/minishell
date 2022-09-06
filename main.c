/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:43:13 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/06 06:09:28 by root             ###   ########.fr       */
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
		printf("STEX EM ->%d\n", i);
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

int	not_found_second_quote(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			while (line[++i] && line[i] != '\'')
				;
			flag = (line[i] == '\0');
		}
		if (line[i] == '"')
		{
			while (line[++i] && line[i] != '"')
				;
			flag = (line[i] == '\0');
		}
		if (!line[i])
			break ;
		i++;
	}
	if (flag)
		printf("QCI QEZ\n");
	return (flag);
}


void	passwords(char **promt,  int *i)
{
	if((*promt)[*i] && ((*promt)[*i] != '<' && (*promt)[*i] != '>' && (*promt)[*i] != '|'))
	{
		while((*promt)[*i] && (*promt)[*i] != 32)
			(*i)++;
	}
}


int	only_pipe(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i] && (prompt[i] == ' ' || prompt[i] == '\t'))
		;
	if (prompt[i] == '|')
		return (1);
	return (0);
}




int	main(int argc, char **argv, char **env)
{
	char	*promt;
	t_pars	**pars;
//	t_env	*environ;
	int		i;
	int		count;
	char	**cmd;
	(void)argc;
	(void)argv;
	(void)env;
	//i = 0;
	//printf("%x\n", &count);
/*	environ = env_initialization(env);
	print_environment(environ);
	free_env(&environ);
	while (1)
	{
		 code 
	}
	exit(0);
	////////////////////////////////////////////////////////
*/


while(1)
{
i = 0;	
	promt = readline("Minishell ");
	if (!promt )
		return (0);
	// if (ft_strlen(promt) == 0 || not_found_second_quote(promt) || only_pipe(promt))
	// 	continue ;
	if (check_pipes_count(&promt, &count))
	{
		printf("Pipe count--->%d\n", count);
		return(ft_error("Pipe error\n", 1));
	}
	/*pars =(t_pars **)malloc(sizeof(t_pars *) * (count + 1));
	pars[count] = NULL;
	while (i < count)
	{
		pars[i] = (t_pars *)malloc(sizeof(t_pars));
		pars[i]->errfile = NULL;
		i++;
	}*/
	pars = init_struct(count);
	if(!pars)
		return (0);
	if(openheredoc(promt, pars)) // heredocery stexic a bacum
		return(0);
	i = 0;
	if (!lexer(&promt, &pars, '<'))
		return (0);
	if (!lexer(&promt, &pars, '>'))
		return (0);
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
	if (open_processes(count, pars, env) == 0)
		free_pars(pars, count);
	// while(i < count)
	// {
	// 	wait(NULL);
	// 	i++;
	// }
	free_pars(pars, count);
	free(promt);
	
}
	return (0);
}

