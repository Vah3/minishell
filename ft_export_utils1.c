/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:00:10 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/10 22:05:13 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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

void	print_export_err_and_ch_s(char *str, int *i)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	(*i)++;
	g_status = 1;
}
