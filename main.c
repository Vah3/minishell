/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:43:13 by vagevorg          #+#    #+#             */
/*   Updated: 2022/08/29 21:02:36 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_trim_substr(char **source, int start, int end)
{
	char	*ret_string;
	char	*new_string;
	int		i;

	ret_string = ft_substr(*source, start, end - start);
	new_string = malloc(sizeof(char) * (
				ft_strlen(*source) - (end - start) + 1));
	i = -1;
	while ((*source)[++i] && i < start)
		new_string[i] = (*source)[i];
	while ((*source)[end] && end < (int)ft_strlen(*source))
		new_string[i++] = (*source)[end++];
	new_string[i] = '\0';
	free(*source);
	*source = new_string;
	return (ret_string);
}

int	not_found_second_quote(char *line)
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
}


int	ifheredoc(char **promt,char **delim, int *i, int *j)
{
	if ((*promt)[*i] && (*promt)[*i] == '<'  && (*promt)[(*i) + 1] && (*promt)[(*i) + 1] == '<')
	{
		*i += 2;
		if(trimspaces(promt, i, j))
			return (2);
		iffiles(promt, i, j);
	//	delim = ft_trim_substr(promt, *j, *i);
		duporjoin(delim, promt, *i, *j);
		*i = -1;
	}
//	if (!(*promt))
//		return (0);
	return(1);
}

void	passwords(char **promt,  int *i)
{
	if((*promt)[*i] && ((*promt)[*i] != '<' && (*promt)[*i] != '>'))
	{
		while((*promt)[*i] && (*promt)[*i] != 32)
			(*i)++;
	}
}


int	lexer(char **promt, char ***files, char c)
{
	int		i;
	int		j;
	char	*line;

	i = -1;
	line = NULL;
	while ((*promt)[++i])
	{
		skipquotes(promt, &i);
		passwords(promt, &i);
		if(ifheredoc(promt, &line, &i, &j) == 0)
			return (0);
		if ((*promt)[i] && (*promt)[i] == c)
		{
			i++;
			if (trimspaces(promt, &i, &j))
				return (2);
			iffiles(promt, &i, &j);
			if(opener(promt, j, i, c))
				return(0);
//			duporjoin(&line, promt, i, j);
			i = -1;
		}
	}
//	printf("%s", line);
//(void) files;
	if (line)
	{
		*files = ft_split(line, 32);
		free(line);
	}
	return (1);
}

int	main(void)
{
	char	*promt;
	t_pars	pars;
	int		i;

	i = 0;
	promt = readline("Minishell ");
	if (!promt)
		return (0);
	if (not_found_second_quote(promt))
	{
		printf("Quote error\n");
		return (0);
	}
	if (!lexer(&promt, &pars.heredocs, '<'))
		return (0);
//	if (!lexer(&promt, &pars.outfiles, '>'))
//		return (0);
	while (pars.infiles && pars.infiles[i])
	{
		printf("%s\n", pars.infiles[i]);
		free(pars.infiles[i]);
		i++;
	}
	i = 0;
	while (pars.heredocs && pars.heredocs[i])
	{
		printf("%s\n", pars.heredocs[i]);
		free(pars.heredocs[i]);
		i++;
	}
	printf("barii\n");
	return (0);
}
//	printf("%s\n", promt);*/
/*	char *a = "barev dzez vonceq";
	printf("%s\n",ft_trim_substr(&a, 6, 10));
	printf("%s\n",a);*/
//	while(1);
