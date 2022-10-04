/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:18:33 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/04 18:23:53 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (i == 0)
			if (!ft_isalpha(key[i]) && !(key[i] == '_'))
				return (0);
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	call_unset(char *prompt, t_env *env)
{
	char	**splited_prompt;
	int		i;
	t_env	*temp;
	char	*key;
	
	temp = env;
	i = 1;
	splited_prompt = ft_split(prompt, ' ');
	while (splited_prompt[i])
	{
		key = ft_strdup(splited_prompt[i]);
		key = get_correct_cmd(key);
		if (is_valid_key(key))
		{
			if (ft_strcmp(key, "PWD") == 0)	
				update_value(&env, "+PWD", NULL);
			else if (ft_strcmp(key, "OLDPWD") == 0)
				update_value(&env, "+OLDPWD", NULL);
			remove_from_list(env, key);
		}
		else
			printf("minishell: unset: `%s': not a valid identifier\n", key);
		i++;
		free(key);
	}
	free_after_split(splited_prompt);
	return (0);
}