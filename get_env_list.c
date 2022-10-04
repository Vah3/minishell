/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:20:01 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/04 18:24:24 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_element(char *key, char *value)
{
	t_env	*temp;

	temp = (t_env *)malloc(sizeof(t_env));
	if (!temp)
		return (NULL);
	temp->key = ft_strdup(key);
	temp->value = ft_strdup(value);
	temp->next = NULL;
	return (temp);
}

void	env_add_back(t_env **list, t_env *new_item)
{
	t_env	*temp;

	if (*list == NULL)
		*list = new_item;
	else
	{
		temp = last_env_element(*list);
		temp->next = new_item;
	}
}

int	key_len(char *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	return (len);
}

void	set_shlvl(t_env *env)
{
	int	lvl;

	lvl = 0;
	while(env)
	{
		if (!ft_strcmp(env->key, "SHLVL"))
		{
			lvl = ft_atoi(env->value);
			free(env->value);
			lvl++;
			if (lvl < 0)
				lvl = 0;
			if (lvl == 1000)
			{
				env->value = NULL;
				break ;
			}
			else if (lvl > 1000)
			{
				printf("minishell: warning: shell level (%d) too high, resetting to 1\n", lvl);
				lvl = 1;
			}
			env->value = ft_itoa(lvl);
			break;
		}
		env = env->next;
	}
}

t_env	*env_initialization(char **env_)
{
	t_env		*env;
	char		**lines;
	int			length;
	int			i;
	char		*cur_pwd;
	i = -1;
	length = size_of_env(env_);
	env = NULL;
	while (++i < length)
	{
		lines = ft_split(env_[i], '=');
		env_add_back(&env, new_env_element(lines[0], lines[1]));
		free_after_split(lines);
		lines = NULL;
	}
	if(!getenv("?"))
		env_add_back(&env, new_env_element("?", "0"));
	cur_pwd = getcwd(NULL, 0);
	if (!cur_pwd)
		return ((void *)ft_error("CURENT_PWD-n feylvela, pti dzenq\n", 1));
	if (!exists_key("PWD", env))
		env_add_back(&env, new_env_element("PWD", cur_pwd));
	else
		update_value(&env, "PWD", cur_pwd);
	if (!exists_key("OLDPWD", env))
		env_add_back(&env, new_env_element("OLDPWD", NULL));
	else
		update_value(&env, "OLDPWD", NULL);
	set_shlvl(env);
	return (env);
}

void	remove_from_list(t_env *env, char *key)
{
	t_env	*temp;
	t_env	*prev;
	t_env	*tofree;

	temp = env;
	while (temp && ft_strncmp(temp->key, key, ft_strlen(temp->key)))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	tofree = temp;
	prev->next = tofree->next;
	free(tofree->key);
	free(tofree->value);
	free(tofree);
}
