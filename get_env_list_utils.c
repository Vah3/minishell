/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:05:55 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/10 22:14:08 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_lvl(t_env *env, int *lvl)
{
	if (!ft_strcmp(env->key, "SHLVL"))
	{
		*lvl = ft_atoi(env->value);
		free(env->value);
		(*lvl)++;
		if (*lvl <= 0)
			*lvl = 0;
		if (*lvl == 1000)
		{
			env->value = NULL;
			return (1);
		}
		else if (*lvl > 1000)
		{
			printf("minishell: warning: shell level (%d) too "
				"high, resetting to 1\n", *lvl);
			*lvl = 1;
		}
		env->value = ft_itoa(*lvl);
		return (1);
	}
	return (0);
}

void	set_shlvl(t_env *env)
{
	int	lvl;

	lvl = 0;
	while (env)
	{
		if (set_lvl (env, &lvl))
			break ;
		env = env->next;
	}
}

void	set_def_env(char **env_, t_env **env_list)
{
	char		**lines;
	int			length;
	int			i;

	i = -1;
	length = size_of_env(env_);
	*env_list = NULL;
	while (++i < length)
	{
		lines = ft_split(env_[i], '=');
		env_add_back(env_list, new_env_element(lines[0], lines[1]));
		free_after_split(lines);
		lines = NULL;
	}
}

void	set_pwd_oldpwd(t_env *env, char *cur_pwd)
{
	if (!getenv("?"))
		env_add_back(&env, new_env_element("?", "0"));
	if (!exists_key("PWD", env))
		env_add_back(&env, new_env_element("PWD", cur_pwd));
	else
		update_value(&env, "PWD", cur_pwd);
	if (!exists_key("OLDPWD", env))
		env_add_back(&env, new_env_element("OLDPWD", NULL));
	else
		update_value(&env, "OLDPWD", NULL);
}

void	set_additional_pwd_oldpwd(t_env *env, char *cur_pwd)
{
	if (!exists_key("+PWD", env))
		env_add_back(&env, new_env_element("+PWD", cur_pwd));
	else
		update_value(&env, "+PWD", cur_pwd);
	if (!exists_key("+OLDPWD", env))
		env_add_back(&env, new_env_element("+OLDPWD", NULL));
	else
		update_value(&env, "+OLDPWD", NULL);
}
