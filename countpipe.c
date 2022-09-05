/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countpipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:07:22 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/02 14:19:01 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes_count(char **promt, int *count)
{
	int		i;
	char	*newline;

	newline = NULL;
	*count = 1;
	i = 0;
	while ((*promt)[i])
	{
		while ((*promt)[i] && (*promt)[i] != '|')
		{
			skipquotes(promt, &i);
			passwords(promt, &i);
			if((*promt)[i])
				i++;
		}
		if ((*promt)[i] && (*promt)[i] == '|')
		{
			(*count)++;
			i++;
			while ((*promt)[i] && (*promt)[i] == 32)
				i++;
			if ((*promt)[i] && (*promt)[i] == '|')
			{
				(*count)--;
				return (1);
			}
			if (!(*promt)[i])
			{
				while (newline == NULL || ft_strlen(newline) == 0)
					newline = readline(">");
				if (not_found_second_quote(newline))
					return (ft_error("Quote error\n", 1));
				if (only_pipe(newline))
					return (ft_error("There is only pipe\n", 1));
				*promt = ft_strjoin(*promt, " ");
				*promt = ft_strjoin(*promt, newline);
				free(newline);
				newline = NULL;
			}
		}
		if((*promt)[i])
		i++;
	}
	return (0);
}
