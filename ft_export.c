/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:06:45 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/12 19:51:17 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	exists_key(char *key, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	update_value(t_env **env, char *key, char *value)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			break ;
		}
		temp = temp->next;
	}
}

void	do_all_stuff(t_export exp, t_env *env, int *i)
{
	while (exp.splited_prompt[*i])
	{
		exp.splited_prompt[*i] = get_correct_cmd(exp.splited_prompt[*i]);
		if (!is_valid(exp.splited_prompt[*i], &exp.mode))
		{
			print_export_err_and_ch_s(exp.splited_prompt[*i], i);
			continue ;
		}
		get_correct_key_value(exp.splited_prompt[*i], \
			exp.mode, &exp.key, &exp.value);
		if (ft_strchr(exp.splited_prompt[*i], '='))
		{
			if (exp.mode == JOIN_MODE)
			{
				join_and_free(&env, &exp.key, &exp.value, i);
				continue ;
			}
			update_key_values(exp.key, exp.value, env);
		}
		else if (!exists_key(exp.key, env))
			update_and_add(env, exp.key, exp.value);
		free(exp.key);
		free(exp.value);
		(*i)++;
	}
}

int	call_export(char *prompt, t_env *env)
{
	int			i;
	t_export	exp;

	i = 1;
	exp.splited_prompt = ft_split(prompt, ' ');
	if (*exp.splited_prompt && !exp.splited_prompt[1])
		return (print_export(env, exp.splited_prompt));
	do_all_stuff(exp, env, &i);
	free_after_split(exp.splited_prompt);
	return (g_status);
}
