/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:59:08 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/10 17:27:16 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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

int	checks(char **args, int count_of_args, int write)
{
	if (count_of_args == 1)
		return (0);
	if (ft_string_isdigit(args[1]) == 0 || non_numeric(args[1]))
	{
		if (write)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
		}
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

void	free_pars_and_env_list(t_pars **pars)
{
	free_env_(pars[0]->env_var);
	free_pars(pars);
}

int	call_exit(t_pars **pars, char *line)
{
	char	**splited_prompt;
	int		count_of_args;
	int		code;

	count_of_args = -1;
	splited_prompt = ft_split(line, ' ');
	printf("exit\n");
	if (!splited_prompt)
		return (FAILURE);
	if (splited_prompt[1])
		code = ft_atoi_(splited_prompt[1]);
	while (splited_prompt[++count_of_args])
		splited_prompt[count_of_args]
			= get_correct_cmd(splited_prompt[count_of_args]);
	if (count_of_args == 1 || count_of_args == 2
		|| checks(splited_prompt, count_of_args, 0))
		free_pars_and_env_list(pars);
	if (checks(splited_prompt, count_of_args, 1))
	{
		free_after_split(splited_prompt);
		exit (255);
	}
	exiting(count_of_args, code);
	free_after_split(splited_prompt);
	return (0);
}
