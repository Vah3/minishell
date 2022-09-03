/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:20:01 by edgghaza          #+#    #+#             */
/*   Updated: 2022/09/02 17:20:02 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env_element(char *key, char *value)
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

static void	env_add_back(t_env **list, t_env *new_item)
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

t_env	*env_initialization(char **env)
{
	t_env		*environ;
	char		**lines;
	int			length;
	int			i;

	i = -1;
	length = size_of_env(env);
	environ = NULL;
	while (++i < length)
	{
		lines = ft_split(env[i], '=');
		env_add_back(&environ, new_env_element(lines[0], lines[1]));
		free_after_split(lines);
		lines = NULL;
	}
	return (environ);
}

void	print_environment(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
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
	printf("%s=%s\n", tofree->key, tofree->value);
	free(tofree->key);
	free(tofree->value);
	free(tofree);
}
