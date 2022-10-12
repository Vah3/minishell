/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:18:33 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/12 19:59:40 by vagevorg         ###   ########.fr       */
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

void	update_and_remove(t_env **env, char *key, int *ret)
{
	if (is_valid_key(key))
	{
		if (ft_strcmp(key, "PWD") == 0)
			update_value(env, "+PWD", NULL);
		else if (ft_strcmp(key, "OLDPWD") == 0)
			update_value(env, "+OLDPWD", NULL);
		remove_from_list(*env, key);
	}
	else
	{
		*ret = 1;
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(key, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
}

int	call_unset(char *prompt, t_env *env)
{
	char	**splited_prompt;
	int		i;
	int		ret;
	char	*key;

	i = 1;
	ret = 0;
	splited_prompt = ft_split(prompt, ' ');
	while (splited_prompt[i])
	{
		key = ft_strdup(splited_prompt[i]);
		key = get_correct_cmd(key);
		update_and_remove(&env, key, &ret);
		i++;
		free(key);
	}
	free_after_split(splited_prompt);
	return (ret);
}
