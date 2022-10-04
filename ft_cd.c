/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:50:38 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/04 21:34:20 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// || (splited_prompt[1][0] == '-' && ft_strlen(splited_prompt[1]) == 1)--> -depqn a

int	call_cd(char *prompt, t_env *env)
{
	char	**splited_prompt;
	char	*to_go;
	t_env	*key;
	
	splited_prompt = ft_split(prompt, ' ');
	if (!splited_prompt[1])
	{
		if (chdir(_getenv(env, "HOME")) == -1)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			free_after_split(splited_prompt);				
			return (1);
		}
		else
		{
			update_value(&env, "OLDPWD", _getenv(env, "PWD"));
			update_value(&env, "+OLDPWD", _getenv(env, "+PWD"));
			update_value(&env, "PWD", _getenv(env, "HOME"));
			update_value(&env, "+PWD", _getenv(env, "HOME"));
		}
	}
	else
	{
		
	}
	free_after_split(splited_prompt);				
	return (0);
	
}