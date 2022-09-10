/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_correct_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:10:42 by edgghaza          #+#    #+#             */
/*   Updated: 2022/09/10 17:36:39 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	not_found_second_quote(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			while (line[++i] && line[i] != '\'')
				;
			flag = (line[i] == '\0');
		}
		if (line[i] == '"')
		{
			while (line[++i] && line[i] != '"')
				;
			flag = (line[i] == '\0');
		}
		if (!line[i])
			break ;
		i++;
	}
	return (flag);
}*/

char	*get_env_key(char *trash, int *i)
{
	char	*key;
	int		len;
	int		start;
	int		j;
	
	start = (*i) + 1;	
	len = 0;
	(*i) += 1;
	if (ft_isdigit(trash[*i]))
		return (NULL);
	while (trash[*i] && (ft_isalnum(trash[*i]) || trash[*i] == '_'))
	{
		(*i) += 1;
		len++;
	}
	key = (char *)malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	j = 0;
	while (trash[start] && (ft_isalnum(trash[start]) || trash[start] == '_'))
		key[j++] = trash[start++];
	key[j] = '\0';
	return (key);

}

int	correct_len(char *trash, t_env *env_list) 
{
	int		i;
	int		count_of_symbols;
	char	*env_key;
	char	*env_value;

	i = 0;
	count_of_symbols = 0;
	while (trash[i])
	{
		if (trash[i] == '"')
		{
			while (trash[++i] && trash[i] != '"')
			{
				if (trash[i] == '$')
				{
					env_key = get_env_key(trash, &i);
					env_value = _getenv(env_list, env_key);
					free(env_key);
					count_of_symbols += (int)ft_strlen(env_value);
					free(env_value);
				}
				else
					count_of_symbols++;
			}
		
		}
		if (trash[i] == '\'')
		{
			while (trash[++i] && trash[i] != '\'')
				count_of_symbols++;
		}	
		if (trash[i] == '$')
		{
			env_key = get_env_key(trash, &i);
			env_value = _getenv(env_list, env_key);
			free(env_key);
			count_of_symbols += ft_strlen(env_value);
			free(env_value);
		}
		if (!trash[i])
			break ;
		count_of_symbols += (trash[i] != '"' && trash[i] != '\'');
		i++;
	}
	return (count_of_symbols);
}

char	*clear_cmd(char *trash, int count_of_symbols, t_env *env_list)
{
	char	*cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = (char *)(sizeof(char) * count_of_symbols + 1);
	if (!cmd)
		return (NULL);
	while (trash[i])
	{
		if (trash[i] == '"')
			while (trash[++i] && trash[i] != '"')//STUGETL
			{
				if (trash[i] == '$')
					//call_something
				// else
					cmd[j++] = trash[i];
			}
		if (trash[i] == '\'')
			while (trash[++i] && trash[i] != '\'')
				cmd[j++] = trash[i];
		if (!trash[i])
			break ;
		if (trash[i] != '"' && trash[i] != '\'')//STUGETL
			{
				if (trash[i] == '$')
						//call_something
				// else		
					cmd[j++] = trash[i];
			}
		i++;
	}
	cmd[j] = '\0';
	return (cmd);
}

char	*get_expanded_prompt(char *trash, t_env *list_env)
{
	int		count_of_symbols;
	char	*cmd;

	count_of_symbols = correct_len(trash, list_env);
	cmd = clear_cmd(trash, count_of_symbols, list_env);
	printf("%d\n", count_of_symbols);
	printf("%s\n", cmd);
	free(trash);
	return (cmd);
}



// <"A" << "$PATH"  ls -l | cat $PATH
//<"A", "ls "-l, cat $PATH