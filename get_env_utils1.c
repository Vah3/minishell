/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:53:27 by edgghaza          #+#    #+#             */
/*   Updated: 2022/09/25 09:34:57 by root             ###   ########.fr       */
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
	update_status(head);
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

int	count_of_quote(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

char	*set_back_slesh(char *line)
{
	int		i;
	char	*new;
	char	*new1;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\'')
		{
			if (i > 0 && line[i - 1] == '\\' && i++)
				continue ;
			new1 = ft_strdup(line + i + 1);
			line[i] = '\0';
			new = ft_strdup(line);
			new = ft_strjoin(new, "\\'");
			line = ft_strjoin(new, new1);
			free (new1);
			i++;
		}
		i++;
	}
	return (line);
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
	temp->value = set_back_slesh(temp->value);
	return (temp->value);
}
//nayel ardzyoq imast ka dup anel value, arden maloccac a
