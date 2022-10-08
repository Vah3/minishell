/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:06:45 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/08 22:30:48 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	status;

int	exists_key(char *key, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	update_value(t_env **env, char *key, char *value)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			break ;
		}
		temp = temp->next;
	}
}

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

void	print_export_err_and_ch_s(char *str, int *i)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	(*i)++;
	status = 1;
}

char	*get_key(int mode, char *arg)
{
	char	*key;

	key = NULL;
	if (mode == ADD_MODE)
		key = ft_substr(arg, 0, key_len(arg));
	else
		key = ft_substr(arg, 0, (key_len(arg) - 1));
	return (key);
}

void	get_correct_key_value(char *str, int mode, char **key, char **value)
{
	if (ft_strchr(str, '='))
	{
		*value = ft_strdup(ft_strchr(str, '=') + 1);
		*key = get_key(mode, str);
	}
	else
	{
		*key = ft_strdup(str);
		*value = NULL;
	}
}

void	join_and_free(t_env **env, char **key, char **value, int *i)
{
	join_value(env, *key, *value);
	if (ft_strcmp(*key, "PWD") == 0)
		join_value(env, "+PWD", *value);
	else if (ft_strcmp(*key, "OLDPWD") == 0)
		join_value(env, "+OLDPWD", *value);
	(*i)++;
	free(*key);
	free(*value);
}

void	update_key_values(char *key, char *value, t_env *env)
{
	if (exists_key(key, env))
	{
		update_value(&env, key, value);
		if (ft_strcmp(key, "PWD") == 0)
			update_value(&env, "+PWD", value);
		if (ft_strcmp(key, "OLDPWD") == 0)
			update_value(&env, "+OLDPWD", value);
	}
	else
	{
		if (ft_strcmp(key, "PWD") == 0)
			update_value(&env, "+PWD", value);
		else if (ft_strcmp(key, "OLDPWD") == 0)
			update_value(&env, "+OLDPWD", value);
		env_add_back(&env, new_env_element(key, value));
	}
}

void	update_and_add(t_env *env, char *key, char *value)
{	
	if (ft_strcmp(key, "PWD") == 0)
		update_value(&env, "+PWD", value);
	else if (ft_strcmp(key, "OLDPWD") == 0)
		update_value(&env, "+OLDPWD", value);
	env_add_back(&env, new_env_element(key, value));
}

void	do_all_stuff(t_export exp, t_env *env, int *i)
{
	while (exp.splited_prompt[*i])
	{
		exp.splited_prompt[*i] = get_correct_cmd(exp.splited_prompt[*i]);
		if (!is_valid(exp.splited_prompt[*i], &exp.mode))
		{
			print_export_err_and_ch_s(exp.splited_prompt[*i], i);
			continue ;
		}
		get_correct_key_value(exp.splited_prompt[*i], \
			exp.mode, &exp.key, &exp.value);
		if (ft_strchr(exp.splited_prompt[*i], '='))
		{
			if (exp.mode == JOIN_MODE)
			{
				join_and_free(&env, &exp.key, &exp.value, i);
				continue ;
			}
			update_key_values(exp.key, exp.value, env);
		}
		else if (!exists_key(exp.key, env))
			update_and_add(env, exp.key, exp.value);
		free(exp.key);
		free(exp.value);
		(*i)++;
	}
}

int	call_export(char *prompt, t_env *env)
{
	int			i;
	t_export	exp;

	i = 1;
	exp.splited_prompt = ft_split(prompt, ' ');
	if (*exp.splited_prompt && !exp.splited_prompt[1])
		return (print_export(env, exp.splited_prompt));
	do_all_stuff(exp, env, &i);
	free_after_split(exp.splited_prompt);
	return (status);
}
