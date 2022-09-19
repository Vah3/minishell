/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:53:27 by edgghaza          #+#    #+#             */
/*   Updated: 2022/09/19 20:54:14 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_env(t_env	*head, int status)
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
	update_status(head, status);
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
	if (!key)
		return (NULL);
	while (temp && ft_strncmp(temp->key, key, ft_strlen(temp->key)))
		temp = temp->next;
	if (!temp)
		return (NULL);
	return (ft_strdup(temp->value));
}
//nayel ardzyoq imast ka dup anel value, arden maloccac a
