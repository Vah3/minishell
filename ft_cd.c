/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:50:38 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/09 17:10:19 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	call_cd(char *prompt, t_env *env)
{
	char	**splited_prompt;
	char	*cur_pwd;
	
	splited_prompt = ft_split(prompt, ' ');
	if (!splited_prompt[1])
	{
		if (!exists_key("HOME", env))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			free_after_split(splited_prompt);				
			return (1);	
		}
		else if (chdir(_getenv(env, "HOME")) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(_getenv(env, "HOME"), 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			free_after_split(splited_prompt);				
			return (1);
		}
		else
		{
			update_value_cd(&env, "OLDPWD", _getenv(env, "+PWD"));
			update_value(&env, "+OLDPWD", _getenv(env, "+PWD"));
			update_value(&env, "PWD", _getenv(env, "HOME"));
			update_value(&env, "+PWD", _getenv(env, "HOME"));
		}
	}
	else
	{
		if (chdir(splited_prompt[1]) < 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(splited_prompt[1]);
			free_after_split(splited_prompt);
			return (1);
		}
		else
		{
			cur_pwd = getcwd(NULL, 0);
            if (!cur_pwd)
            {
                perror("minishell: can not get curent directory: ");
                free_after_split(splited_prompt);
                return (1);
            }
			update_value(&env, "OLDPWD", _getenv(env, "+PWD"));
			update_value(&env, "+OLDPWD", _getenv(env, "+PWD"));
			update_value(&env, "PWD", cur_pwd);
			update_value(&env, "+PWD", cur_pwd);
			free(cur_pwd);
		}
	}
	free_after_split(splited_prompt);				
	return (0);
}

int	call_pwd(t_env *list)
{
	
	char		*pwd;
	size_t		size;

	size = 1024;
	pwd = NULL;
	pwd = getcwd(pwd, size);
	if (pwd)
		ft_putendl_fd(pwd, 1);
	else
		ft_putendl_fd(_getenv(list, "PWD"),1);
	free(pwd);
	return (0);
}
