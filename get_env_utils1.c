/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:53:27 by edgghaza          #+#    #+#             */
/*   Updated: 2022/09/06 15:11:06 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_env(t_env	*head)
{
	t_env	*temp;
	char	**env;
	char	*line;
	int		i;

	env = malloc(sizeof(char *) * (size_of_list(head) + 1));
	if (!env)
		return (NULL);
	i = 0;
	temp = head;
	line = NULL;
	while (temp)
	{
		line = ft_strdup(temp->key);
		line = ft_strjoin(line, "=");
		line = ft_strjoin(line, temp->value);
		env[i++] = ft_strdup(line);
		free(line);
		line = NULL;
		temp = temp->next;
	}
	env[i] = NULL;
	return (env);
}

void	env_replace(t_env *env, char *key, char *value)
{
	t_env	*temp;

	temp = env;
	while (temp && ft_strncmp(temp->key, key, ft_strlen(temp->key)))
		temp = temp->next;
	if (!temp)
		return ;
	free(temp->value);
	temp->value = ft_strdup(value);
}

char	*_getenv(t_env *list, char *key )
{
	t_env	*temp;

	temp = list;
	while (temp && ft_strncmp(temp->key, key, ft_strlen(temp->key)))
		temp = temp->next;
	if (!temp)
		return (NULL);
	return (ft_strdup(temp->value));
}
