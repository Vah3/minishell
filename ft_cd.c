/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:50:38 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/10 16:21:17 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home(t_env *env, char **splited_prompt)
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
		free_after_split(splited_prompt);
		return (0);
	}
}

int	cd_other_place(t_env *env, char **splited_prompt, char	*cur_pwd)
{
	int		return_value;

	if (chdir(splited_prompt[1]) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(splited_prompt[1]);
		return_value = 1;
	}
	else
	{
		cur_pwd = getcwd(NULL, 0);
		if (!cur_pwd)
		{
			perror("minishell: can not get curent directory: ");
			return_value = 1;
		}
		update_value(&env, "OLDPWD", _getenv(env, "+PWD"));
		update_value(&env, "+OLDPWD", _getenv(env, "+PWD"));
		update_value(&env, "PWD", cur_pwd);
		update_value(&env, "+PWD", cur_pwd);
		free(cur_pwd);
		return_value = 0;
	}
	free_after_split(splited_prompt);
	return (return_value);
}

int	call_cd(char *prompt, t_env *env)
{
	char	**splited_prompt;
	char	*cur_pwd;

	cur_pwd = NULL;
	splited_prompt = ft_split(prompt, ' ');
	if (!splited_prompt[1])
		return (cd_home(env, splited_prompt));
	else
		return (cd_other_place(env, splited_prompt, cur_pwd));
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
		ft_putendl_fd(_getenv(list, "PWD"), 1);
	free(pwd);
	return (0);
}
