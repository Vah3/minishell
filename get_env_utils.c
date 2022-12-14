/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:20:27 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/08 19:47:21 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_(t_env **env)
{
	t_env	*temp;

	while (env && *env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		temp = NULL;
	}
}

t_env	*last_env_element(t_env *start)
{
	if (start == NULL)
		return (NULL);
	if (start->next == NULL)
		return (start);
	else
		return (last_env_element(start->next));
}

int	size_of_list(t_env *list)
{
	if (list == NULL)
		return (0);
	else
		return (1 + size_of_list(list->next));
}

void	free_after_split(char **store)
{
	int	i;

	i = 0;
	while (store && store[i])
	{
		free(store[i]);
		store[i] = NULL;
		i++;
	}
	free(store);
}

int	size_of_env(char **env)
{
	int	length;

	length = 0;
	while (env && env[length])
		length++;
	return (length);
}
