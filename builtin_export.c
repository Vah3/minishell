/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:27:18 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/04 18:25:24 by edgghaza         ###   ########.fr       */
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

	splited_str = NULL;
	splited_str = ft_split(str, ' ');
	if (!splited_str)
		return (0);
	splited_str[0] = get_correct_cmd(splited_str[0]);
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

static size_t	ft_atoi_(const char *str)
{
	int	index;
	int	convert;
	int	sign;

	index = 0;
	convert = 0;
	sign = 1;
	if (!str)
		return (0);
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -sign;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		convert = convert * 10 + str[index] - '0';
		index++;
	}
	return (sign * convert);
}

int	ft_string_isdigit(char *str)
{
	int i;

	i = 0;
    while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i < (int)ft_strlen(str))
		return (0);
    return (1);
}

int	call_exit(char *line)
{
	char	**splited_prompt;
	int len;

	len = 0;
	splited_prompt = ft_split(line, ' ');
	if (!splited_prompt)
		return (FAILURE);
	while(splited_prompt[len])
		len++;
	printf("%d\n",len);
	if (len == 1)
		exit(0);
	return (0);
}

	int	call_builtin(char *prompt, int id, t_env *env)
	{
		if(id == IS_ECHO)
			return(call_echo(prompt));//call_echo(prompt, env);
		else if (id == IS_CD)
				return(call_cd(prompt, env));//<------------------------------------------
		else if (id == IS_PWD)
			return(printf("hi\n"));//call_pwd(prompt, env);
		else if (id == IS_EXPORT)
			return(call_export(prompt, env));
		else if (id == IS_UNSET)
			return (call_unset(prompt, env));//call_unset(prompt, env);
		else if (id == IS_ENV)
			return (call_env(env));
		else if (id == IS_EXIT)
			return (call_exit(prompt));
			//return(printf("hi\n"));//call_exit(prompt, env);
			return (0);
	}