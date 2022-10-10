/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:53:27 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/10 22:15:21 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_init(t_env *head, int *i, char **env)
{
	t_env	*temp;
	char	*line;

	line = NULL;
	temp = head;
	while (temp)
	{
		if (is_valid_key(temp->key)
			&& (temp->value || ft_strcmp(temp->key, "SHLVL") == 0))
		{
			line = ft_strdup(temp->key);
			line = ft_strjoin(line, "=");
			line = ft_strjoin(line, temp->value);
			env[(*i)++] = ft_strdup(line);
			free(line);
			line = NULL;
		}
		temp = temp->next;
	}
}

char	**list_to_env(t_env	*head)
{
	char	**env;
	int		i;

	env = malloc(sizeof(char *) * (size_of_list(head) + 1));
	if (!env)
		return (NULL);
	i = 0;
	update_status(head);
	env_init(head, &i, env);
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
