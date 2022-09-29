/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:27:18 by edgghaza          #+#    #+#             */
/*   Updated: 2022/09/29 20:36:21 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_spaces(char *str, int *i)
{
	while(str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			(*i)++;
}

int	are_equal(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] && to_find[i])
	{
		if (str[i] != to_find[i])
			return (0);
		i++;
	}
	return (1);
}
	// do_export(splited_str, env_list);
int there_is_builtin(char *str)
{
	char **splited_str;
	int		id;
	splited_str = ft_split(str, ' ');
	if(ft_strcmp(splited_str[0], "echo") == 0)
		id = IS_ECHO;
	else if(ft_strcmp(splited_str[0], "cd") == 0)
		id = IS_CD;
	else if(ft_strcmp(splited_str[0], "pwd") == 0)
		id = IS_PWD;
	else if(ft_strcmp(splited_str[0], "export") == 0)
		id = IS_EXPORT;
	else if(ft_strcmp(splited_str[0], "unset") == 0)
		id = IS_UNSET;
	else if(ft_strcmp(splited_str[0], "env") == 0)
		id = IS_ENV;
	else if(ft_strcmp(splited_str[0], "exit") == 0)
		id = IS_EXIT;
	else
		id = 0;
	free_after_split(splited_str);
	return (id);
}

	int	call_builtin(char *prompt, int id, t_env *env)
	{
		if(id == IS_ECHO)
			return(printf("hi\n"));//call_echo(prompt, env);
		else if (id == IS_CD)
			return(printf("hi\n"));//call_cd((prompt, env));
		else if (id == IS_PWD)
			return(printf("hi\n"));//call_pwd(prompt, env);
		else if (id == IS_EXPORT)
			return(call_export(prompt, env));
		else if (id == IS_UNSET)
			return(printf("hi\n"));//call_unset(prompt, env);
		else if (id == IS_ENV)
			return(printf("hi\n"));//call_env(prompt, env);
		else if (id == IS_EXIT)
			return(printf("hi\n"));//call_exit(prompt, env);
			return (0);
	} 
// int	are_equal(char *str, char *to_find)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && to_find[i])
// 	{
// 		if (str[i] != to_find[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
	
// }

// int there_is_export(char *str, int *i)
// {
// 	skip_spaces(str, i);
// 	if (are_equal((str + (*i)), ("export")))
// 		(*i) += 6;
// 	else
// 		return (0);
// 	if (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\0')
// 	{
// 		// printf("SUCCESS\n");
// 		return (1);
// 	}	
// 	return (0);
// }

// int	do_export(char *str, t_env *env)
// {
// 	t_export	all;
// 	int			i;
// 	char		*trash;
	
// 	i = 0;
// 	if (there_is_export(str, &i))
// 	{
// 		skip_spaces(str, &i);
// 		trash = ft_strdup(str + i);
		
// 	}
// }