/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:52:29 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/10 22:22:41 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	update_status(t_env *env)
{
	t_env	*local_env;
	char	*stat;

	local_env = env;
	stat = NULL;
	while (local_env)
	{
		if (ft_strncmp(local_env->key, "?", 1) == 0)
		{
			stat = ft_itoa(g_status);
			free(local_env->value);
			local_env->value = stat;
		}
		local_env = local_env->next;
	}
}

char	*change_delim_key(char *delim)
{
	char	*new_key;

	new_key = NULL;
	if (ft_strcmp(delim, "PWD") == 0)
	{
		new_key = ft_strdup("+PWD");
		free(delim);
		return (new_key);
	}
	else if (ft_strcmp(delim, "OLDPWD") == 0)
	{
		new_key = ft_strdup("+OLDPWD");
		free (delim);
		return (new_key);
	}
	return (delim);
}
