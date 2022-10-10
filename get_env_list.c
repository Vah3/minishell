/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:20:01 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/10 22:12:39 by edgghaza         ###   ########.fr       */
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

t_env	*env_initialization(char **env)
{
	t_env		*env_list;
	char		*cur_pwd;

	env_list = NULL;
	cur_pwd = getcwd(NULL, 0);
	set_def_env(env, &env_list);
	set_pwd_oldpwd(env_list, cur_pwd);
	set_additional_pwd_oldpwd(env_list, cur_pwd);
	set_shlvl(env_list);
	if (!cur_pwd)
	{
		printf("minishell-init: error retrieving current directory: "
			"getcwd: cannot access parent directories: "
			"No such file or directory\n");
		return (env_list);
	}
	free(cur_pwd);
	return (env_list);
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
