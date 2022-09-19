/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_correct_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:10:42 by edgghaza          #+#    #+#             */
/*   Updated: 2022/09/19 20:11:32 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	correct_len(char *trash)
{
	int	i;
	int	count_of_symbols;

	i = 0;
	count_of_symbols = 0;
	while (trash[i])
	{
		if (trash[i] == '"')
		{
			while (trash[++i] && trash[i] != '"')
				count_of_symbols++;
		}
		if (trash[i] == '\'')
		{
			while (trash[++i] && trash[i] != '\'')
				count_of_symbols++;
		}
		if (!trash[i])
			break ;
		count_of_symbols += (trash[i] != '"' && trash[i] != '\'');
		i++;
	}
	return (count_of_symbols);
}

static char	*clear_cmd(char *trash, int count_of_symbols)
{
	char	*cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = (char *)malloc(sizeof(char) * count_of_symbols + 1);
	if (!cmd)
		return (NULL);
	while (trash[i])
	{
		if (trash[i] == '"')
			while (trash[++i] && trash[i] != '"')
				cmd[j++] = trash[i];
		if (trash[i] == '\'')
			while (trash[++i] && trash[i] != '\'')
				cmd[j++] = trash[i];
		if (!trash[i])
			break ;
		if (trash[i] != '"' && trash[i] != '\'')
			cmd[j++] = trash[i];
		i++;
	}
	cmd[j] = '\0';
	return (cmd);
}

char	*get_correct_cmd(char *trash)
{
	int		count_of_symbols;
	char	*cmd;

	count_of_symbols = correct_len(trash);
	cmd = clear_cmd(trash, count_of_symbols);
	free(trash);
	return (cmd);
}
