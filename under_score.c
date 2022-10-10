/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   under_score.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:40:30 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/10 18:37:44 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	there_is_pipe(char *prompt, t_env *env_list)
{
	int	i;

	i = 0;
	while (prompt && prompt[i])
	{
		skipquotes(&prompt, &i);
		if (prompt[i] == '|')
		{
			free(env_list->value);
			env_list->value = NULL;
			return (1);
		}
		if (prompt[i])
			i++;
	}
	return (0);
}

char	**change_under_score(t_env *env_list, char *prompt, char **env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = env_list;
	while (env_list && ft_strcmp(env_list->key, "_"))
		env_list = env_list->next;
	if (there_is_pipe(prompt, env_list))
	{
		free_after_split(env);
		return (list_to_env(head));
	}
	i = ft_strlen(prompt) - 1;
	while (prompt && i > 0 && prompt[i] == 32)
		i--;
	while (prompt && i > 0 && prompt[i] != 32)
		i--;
	if (i >= 0 && !ft_strnstr(prompt + i, "$_", 2))
	{
		free(env_list->value);
		env_list->value = ft_strdup(ft_strrchr(prompt, 32));
	}
	free_after_split(env);
	return (list_to_env(head));
}
