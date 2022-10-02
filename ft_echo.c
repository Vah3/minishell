/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:12:41 by edgghaza          #+#    #+#             */
/*   Updated: 2022/10/02 20:45:37 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*--------->PRINTFY KAROXA POXVI FT_PUTSTR_FD<-----------------*/


int	is_all_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			 return (0);
		i++;
	}
	return (1);
}

int	call_echo(char *prompt)
{
	char	**splited_prompt;
	int		i;
	int		flag;
	
	i = 1;
	flag = 1;
	splited_prompt = ft_split(prompt, ' ');
	while (splited_prompt[i] && is_all_n(splited_prompt[i]))
	{
		flag = 0;
		i++;
	}
	while (splited_prompt[i])
	{
		if (!splited_prompt[i + 1])
			printf("%s", splited_prompt[i]);
		else
			printf("%s ", splited_prompt[i]);
		i++;
	}
	if (flag)
		printf("\n");
	free_after_split(splited_prompt);
	return (0);
}