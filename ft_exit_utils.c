/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:55:23 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/10 22:16:35 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	ft_string_isdigit(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] && str[i + 1] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	i++;
	if (i < (int)ft_strlen(str))
		return (0);
	return (1);
}

int	non_numeric(char *str)
{
	int		len;
	int		i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' && str++)
		i = -1;
	else if (str[i] == '+')
		str++;
	while (str && *str == '0')
		str++;
	len = ft_strlen(str);
	if (len > 19)
		return (1);
	if (len == 19)
	{
		if (i == -1)
			i = ft_strcmp(str, "9223372036854775808");
		else
			i = ft_strcmp(str, "9223372036854775807");
		if (i > 0)
			return (1);
	}
	return (0);
}

void	exiting(int count_of_args, int code)
{
	if (count_of_args == 1)
		exit(g_status);
	else if (count_of_args == 2)
		exit(code);
	else if (count_of_args > 2)
	{
		g_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
}

char	*_getenv(t_env *list, char *key )
{
	t_env	*temp;

	temp = list;
	if (!key)
		return (NULL);
	while (temp && ft_strncmp(temp->key, key, ft_strlen(temp->key)))
		temp = temp->next;
	if (!temp)
		return (NULL);
	temp->value = set_back_slesh(temp->value);
	return (temp->value);
}
