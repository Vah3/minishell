/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:59:08 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/06 18:00:31 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int status;

static unsigned char	ft_atoi_(const char *str)
{
	int		index;
	long	convert;
	int		sign;

	index = 0;
	convert = 0;
	sign = 1;
	if (!str)
		return (0);
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -sign;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		convert = convert * 10 + str[index] - '0';
		index++;
	}
	return ((unsigned char)(sign * convert));
 }

 int	ft_string_isdigit(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if(str[i] && str[i + 1] && (str[i] == '-' || str[i] == '+'))
		i++;
    while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i < (int)ft_strlen(str))
		return (0);
    return (1);
}

int non_numeric(char *str)
{
	int len;
	int i;
	char	*max;
	char	*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		i = -1;
		str++;
	}
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
			i = ft_strcmp(str, min);
		else
			i = ft_strcmp(str, max);
		if (i > 0)
			return (1);
	}
	return (0);
}

int	checks(char **args, int count_of_args)
{
	int	i;

	i = 1;
	if (count_of_args == 1)
		return (1);
	if(ft_string_isdigit(args[1]) == 0 || non_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1],2);
		ft_putendl_fd(": numeric argument required", 2);
		return (1);
	}
	return (0);
}


int	call_exit(char *line)
{
	char	**splited_prompt;
	int count_of_args;

	count_of_args = 0;
	splited_prompt = ft_split(line, ' ');
	printf("exit\n");
	if (!splited_prompt)
		return (FAILURE);
	while(splited_prompt[count_of_args])
	{
		splited_prompt[count_of_args] = get_correct_cmd(splited_prompt[count_of_args]);
		count_of_args++;
	}
	if (checks(splited_prompt, count_of_args))
		exit (255);
	if (count_of_args == 1)
		exit(0);
	else if (count_of_args == 2)
		exit(ft_atoi_(splited_prompt[1]));
	else if (count_of_args > 2)
	{
		status = 1;
		ft_putendl_fd("bash: exit: too many arguments", 2);
	}
	return (0);
}