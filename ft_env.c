/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:25:22 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/01 21:15:46 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call_env(t_env *env)
{
	t_env	*temp;
	
	temp = env;
	while (temp)
	{		
		if ((ft_strcmp(temp->key, "?") == 0))
		{
			temp = temp->next;	
			continue;
		}
		if ((ft_strcmp(temp->key, "SHLVL") == 0) && !temp->value)
		{
			printf("%s=\n", temp->key);
			temp = temp->next;	
			continue;
		}
		if (!temp->value)
		{
			temp = temp->next;	
			continue;
		}
		if (temp->key && temp->value)
		{
			printf("%s=%s\n", temp->key, temp->value);
			temp = temp->next;
		}
	}
	return (0)
;}