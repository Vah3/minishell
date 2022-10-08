/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:27:18 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/08 19:15:35 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	status;

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
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

int	there_is_builtin2(char *splited_prompt)
{
	int	id;

	if (ft_strcmp(splited_prompt, "unset") == 0)
		id = IS_UNSET;
	else if (ft_strcmp(splited_prompt, "env") == 0)
		id = IS_ENV;
	else if (ft_strcmp(splited_prompt, "exit") == 0)
		id = IS_EXIT;
	else
		id = 0;
	return (id);
}

int	there_is_builtin(char *str)
{
	char	**splited_str;
	int		id;

	splited_str = NULL;
	splited_str = ft_split(str, ' ');
	if (!splited_str)
		return (0);
	splited_str[0] = get_correct_cmd(splited_str[0]);
	if (ft_strcmp(splited_str[0], "echo") == 0)
		id = IS_ECHO;
	else if (ft_strcmp(splited_str[0], "cd") == 0)
		id = IS_CD;
	else if (ft_strcmp(splited_str[0], "pwd") == 0)
		id = IS_PWD;
	else if (ft_strcmp(splited_str[0], "export") == 0)
		id = IS_EXPORT;
	else
		id = there_is_builtin2(splited_str[0]);
	free_after_split(splited_str);
	return (id);
}

int	call_builtin(t_pars **pars, char *prompt, int id, t_env *env)
{
	if (id == IS_ECHO)
		return (call_echo(prompt));
	else if (id == IS_CD)
		return (call_cd(prompt, *(pars[0]->env_var)));
	else if (id == IS_PWD)
		return (call_pwd());
	else if (id == IS_EXPORT)
		return (call_export(prompt, *(pars[0]->env_var)));
	else if (id == IS_UNSET)
		return (call_unset(prompt, *(pars[0]->env_var)));
	else if (id == IS_ENV)
		return (call_env(env));
	else if (id == IS_EXIT)
		return (call_exit(pars, prompt));
	return (0);
}
