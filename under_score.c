/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   under_score.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:40:30 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/10 17:43:26 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_dol_us(char *prompt, int i)
{
	return (prompt && i >= 0 && prompt[i] && prompt[i] == '$'
		&& prompt[i + 1] && prompt[i + 1] == '_'
		&& (!prompt[i + 2] || (prompt[i + 2] && prompt[i + 2] == 32)));
}

char	**change_under_score(t_env *env_list, char *prompt, char **env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = env_list;
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, "_"))
			break ;
		env_list = env_list->next;
	}
	while (prompt && prompt[i])
	{
		skipquotes(&prompt, &i);
		if (prompt[i] == '|')
		{
			free(env_list->value);
			env_list->value = NULL;
			free_after_split(env);
			return (list_to_env(head));
		}
		if (prompt[i])
			i++;
	}
	i = ft_strlen(prompt) - 1;
	while (prompt && i > 0 && prompt[i] == 32)
		i--;
	while (prompt && i > 0 && prompt[i] != 32)
		i--;
	if (prompt && i >= 0 && prompt[i] && prompt[i] == '$' && prompt[i + 1] && prompt[i + 1] == '_' && (!prompt[i + 2] || (prompt[i + 2] && prompt[i + 2] == 32)))
	{
		free(env_list->value);
		env_list->value = ft_strdup(ft_strrchr(prompt, 32));
	}
	free_after_split(env);
	return (list_to_env(head));
}
