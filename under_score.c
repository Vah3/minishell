/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   under_score.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:40:30 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/08 18:25:22 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**change_under_score(t_env *env_list, char *promt, char **env)
{
	int		i;
	t_env *head;

	i = 0;
	head = env_list;
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, "_"))
			break;
		env_list = env_list->next;
	}
	while(promt && promt[i])
	{
		skipquotes(&promt, &i);
		if (promt[i] == '|')
		{
			free(env_list->value);
			env_list->value = NULL;
			free_after_split(env);
			return(list_to_env(head));
		}
		if(promt[i])
			i++;
	}
	i = ft_strlen(promt) - 1;
	while(promt && i > 0 && promt[i] == 32)
		i--;
	while(promt && i > 0 && promt[i] != 32)
		i--;
	if (promt && i >= 0 && promt[i] && promt[i] == '$' && promt[i + 1] && promt[i + 1] == '_' && (!promt[i + 2] || (promt[i + 2] && promt[i + 2] == 32)))
	{
		free(env_list->value);
		env_list->value = ft_strdup(ft_strrchr(promt, 32));
	}
	free_after_split(env);
	return(list_to_env(head));	
}