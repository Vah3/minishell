/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:38 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/01 18:00:47 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**make_pipe_for_doc(int count)
{
	int i;
	int	**fd;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * (count + 1));
	if(!fd)
		return (0);
	fd[count] = 0;
	while (i < count)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2); // 2 te 3 stugel
		if (!fd[i])
		{
			while (i > 0)
			{
				i--;
				free(fd[i]);
			}
			free(fd);
		}
			return (0);
		i++;
	}
	return (fd);
}




int	openheredoc(char *promt, t_pars **pars)
{
	int	i;
	int	doc_count;

	i = -1;
	doc_count = 0;
	while (promt[++i])
	{
		skipquotes(&promt, &i);
		passwords(&promt, &i);
		if (promt[i] && promt[i] == '<' && promt[++i]
			&& promt[i] && promt[i] == '<' && promt[++i])
		{
			doc_count++;
			while (promt[i] && promt[i] == 32)
				i++;
			if (promt[i] == '\0' || promt[i] == '|'
				|| promt[i] == '<' || promt[i] == '>')
			{
				printf("sytax error\n");
				return (1);
			}
		}
	}
	write_docs(promt, doc_count, pars);
	return (0);
}

int	write_in_pipe_and_dup(t_pars **pars, int count, char *delim, int z)
{
	int	fd[2];
	char		*line;

	pipe(fd);
	line = readline(">");
	write(fd[0], &line, ft_strlen(line));
	while(count > 0)
	{
		if(!ft_strncmp(delim, line, ft_strlen(line)))
		{
			count--;
			break;
		}
		line= readline(">");
		write(fd[0], &line, ft_strlen(line));
	}
	close(fd[0]);
	(*pars)[z].isheredoc = dup(fd[1]);
	free(delim);
	return (0);
}



void	write_docs(char *promt, int count, t_pars **pars)
{
	int i;
	int j;
	int z;
	char	*delim;

	z = 0;
	i = -1;
	while(promt[++i])
	{
		skipquotes(&promt, &i);
		passwords(&promt, &i);
		if(promt[i] == '|')
			z++;
		if (promt[i] && promt[i] == '<' && promt[++i]
			&& promt[i] && promt[i] == '<' && promt[++i])
		{
			while(promt[i] && promt[i] == 32)
				i++;
			if(!promt[i])
			{
				printf("syntax error\n"); // functiony sarqel int typei
				return ;
			}
			j = i;
			while(promt[i] && promt[i] != 32)
				i++;
			delim = ft_substr(promt, j, i - 1);
			write_in_pipe_and_dup(pars, count, delim, z);
			}
	}
}
