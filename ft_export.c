/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:06:45 by edgghaza          #+#    #+#             */
/*   Updated: 2022/09/29 21:14:21 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			break;
		temp = temp->next;
	}
	free(temp->value);
	temp->value = ft_strdup(value);
	
}


int	is_valid(char *str)
{
	int i;

	i = 0;
	if (str && ft_strlen(str) == 0)
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (i == 0)
			if (!ft_isalpha(str[i]) && !(str[i] == '_'))
				return (0);
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);	
}

int print_export(t_env *env)
{
	t_env *temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->key, "?", 1) == 0)
			temp = temp->next;
		if (temp && temp->value == NULL)
		{
			printf("declare -x ");
			printf("%s\n", temp->key);
		}
		else if (temp)
		{
			printf("declare -x ");
			printf("%s=\"", temp->key);
			printf("%s\"\n", temp->value);
		}
		else 
			break;
		temp = temp->next;
	}	
	return (SUCCESS);
}

int call_export(char *prompt, t_env *env)
{
	int		i;
	int		status;
	char 	**splited_prompt;
	char	*key;
	char	*value;

	status = 0;
	i = 1;
	splited_prompt = ft_split(prompt, ' ');
	if (*splited_prompt && !splited_prompt[1])
		return (print_export(env));
	while (splited_prompt[i])
	{
		// printf("-------%s\n",splited_prompt[i]);
		splited_prompt[i] = get_correct_cmd(splited_prompt[i]);
		if (!is_valid(splited_prompt[i]))
		{
			ft_putstr_fd("minishell: export: `",2);
			ft_putstr_fd(splited_prompt[i], 2);
			ft_putstr_fd("\': not a valid identifier\n",2);			
			i++;
			status = 1;
			continue;
		}
		if (ft_strchr(splited_prompt[i], '='))
		{
			value = ft_strdup(ft_strchr(splited_prompt[i], '=') + 1);		
			key = ft_substr(splited_prompt[i], 0, key_len(splited_prompt[i]));
		}
		else
		{
			key =(ft_strdup(splited_prompt[i]));		
			value = NULL;
		}
		if (ft_strchr(splited_prompt[i], '='))
		{	
			if (exists_key(key, env))
				update_value(&env, key, value);
			else
				env_add_back(&env, new_env_element(key, value));
		}
		else if (!exists_key(key, env))
			env_add_back(&env, new_env_element(key, value));
		free(key);
		free(value);
		i++;
	}

	return (status);	
}