/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countpipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:07:22 by vagevorg          #+#    #+#             */
/*   Updated: 2022/08/31 16:36:23 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes_count(char **promt, int *count)
{
	int	i;
	char	*newline;

	newline = NULL;
	*count = 1;
	i = 0;
	while((*promt)[i])
	{
		while ((*promt)[i] && (*promt)[i] != '|')
		{
			skipquotes(promt, &i);
			passwords(promt, &i);
			i++;
		}
		if ((*promt)[i] == '|')
		{
			(*count)++;
			i++;
			while ((*promt)[i] && (*promt)[i] == 32)
				i++;
			if ((*promt)[i] == '|')
			{
				(*count)--;
				return (1);
			}
			if ((*promt)[i] == '\0')
			{
				while (newline == NULL || ft_strlen(newline) == 0)// (newline && newline[0] == 10))
					newline = readline(">");
				//printf("%s",newline);
				if (not_found_second_quote(newline))
				{
					printf("Quote error\n");
					return(1);
				}
				*promt = ft_strjoin(*promt, " ");
				*promt = ft_strjoin(*promt, newline);
				free(newline);
				newline = NULL;
			}
		}
		i++;
	}
	return(0);
}
