/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:02:41 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/10 22:05:23 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_value_cd(t_env **env, char *key, char *value)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup_env(value);
			break ;
		}
		temp = temp->next;
	}
}

void	join_value(t_env **env, char *key, char *value)
{
	t_env	*temp;

	temp = *env;
	if (!exists_key(key, *env))
	{
		env_add_back(env, new_env_element(key, value));
		return ;
	}
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
			break ;
		temp = temp->next;
	}
	temp->value = ft_strjoin(temp->value, value);
}

int	is_valid(char *str, int *mode)
{
	int	i;

	i = 0;
	*mode = ADD_MODE;
	if (str && ft_strlen(str) == 0)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	i--;
	if (str[0] == '+' || str[0] == '=')
		return (0);
	if (str[i] == '+')
	{
		*mode = JOIN_MODE;
		i--;
	}
	while (i >= 0)
	{
		if (i == 0 && !ft_isalpha(str[i]) && !(str[i] == '_'))
			return (0);
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i--;
	}
	return (1);
}

int	print_export(t_env *env, char **splited_prompt)
{
	t_env	*temp;

	temp = env;
	free_after_split(splited_prompt);
	while (temp)
	{
		if (temp && is_valid_key(temp->key) && temp->value == NULL)
		{
			printf("declare -x ");
			printf("%s\n", temp->key);
		}
		else if (temp && is_valid_key(temp->key))
		{
			printf("declare -x ");
			printf("%s=\"", temp->key);
			printf("%s\"\n", temp->value);
		}
		temp = temp->next;
	}	
	return (SUCCESS);
}

void	update_and_add(t_env *env, char *key, char *value)
{	
	if (ft_strcmp(key, "PWD") == 0)
		update_value(&env, "+PWD", value);
	else if (ft_strcmp(key, "OLDPWD") == 0)
		update_value(&env, "+OLDPWD", value);
	env_add_back(&env, new_env_element(key, value));
}
