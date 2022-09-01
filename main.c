/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:43:13 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/01 17:21:45 by vagevorg         ###   ########.fr       */
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


int	ifheredoc(char **promt,int *fileordoc, int *i, int *j)
{
	char *delim;

	if ((*promt)[*i] && (*promt)[*i] == '<'  && (*promt)[(*i) + 1] && (*promt)[(*i) + 1] == '<')
	{
		*i += 2;
		if(trimspaces(promt, i, j))
			return (2);
		iffiles(promt, i, j);
		delim = ft_trim_substr(promt, *j, *i);
		free(delim);
		*fileordoc = 1;
		//duporjoin(delim, promt, *i, *j);
		*i = -1;
	}
//	if (!(*promt))
//		return (0);
	return(1);
}

void	passwords(char **promt,  int *i)
{
	if((*promt)[*i] && ((*promt)[*i] != '<' && (*promt)[*i] != '>' && (*promt)[*i] != '|'))
	{
		while((*promt)[*i] && (*promt)[*i] != 32)
			(*i)++;
	}
}




int	lexer(char **promt, t_pars ***pars, char c)
{
	int		i;
	int		j;
	char	*line;
	int		k;
//	char	**file;

	i = -1;
	k = 0;
	line = NULL;
	while ((*promt)[++i])
	{
		skipquotes(promt, &i);
		passwords(promt, &i);
		if((*promt)[i] == '|')
			k++;
		if(ifheredoc(promt, &((*pars)[k])->fileordoc, &i, &j) == 0)
			return (0);
		if ((*promt)[i] && (*promt)[i] == c)
		{
			i++;
			(*pars)[k]->fileordoc = 0;
			if (trimspaces(promt, &i, &j))
				return (2);
			iffiles(promt, &i, &j);
			if(opener(promt, j, i, c, &((*pars)[k])))
				return(0);
//			duporjoin(&line, promt, i, j);
			i = j - 1;
		}
	}
	printf("-------%d\n", k);
//(void) files;
/*	if (line)
	{
		files = ft_split(line, 32);
		free(line);
	}*/
	
	return (1);
}



/*
void	write_docs(char *promt, int count, t_pars **pars)
{
	int	**fd;
	int i;
	int j;
	int k = 0;
	int z = 0;
	char	*delim;
	char	*line;
//	char 	**delimetrs;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * (count + 1));
	fd[count] = 0;
	while(i < count)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2); // 2 te 3 stugel
		i++;
	}
	i = 0;
//	line == ft_strdup(promt);
//	ifheredoc()
	while(promt[i])
	{
		skipquotes(&promt, &i);
		passwords(&promt, &i);
		if(promt[i] == '|')
			z++;
		if(promt[i] && promt[i] == '<')
		{
			i++;
			if(promt[i] && promt[i] == '<')
			{
				i++;
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
				pipe(fd[k]);
				line = readline(">");
			//	printf("-----%s\n",delim);
				write(fd[k][0], &line, ft_strlen(line));
				while(count > 0)
				{
					if(!ft_strncmp(delim, line, ft_strlen(line)))
					{
						count--;
						break;
					}
					line= readline(">");
					write(fd[k][0], &line, ft_strlen(line));

				}
				close(fd[k][0]);
				(*pars)[z].isheredoc = dup(fd[k][1]);
				k++;
			}
		}
	//	i++;
	//	if(promt[i] == '|')
	//		z++;
		i++;
	}
}


int	openheredoc(char *promt, t_pars **pars)
{
	int i;
	int	doc_count;

	i = 0;
	doc_count = 0;
	while(promt[i])
	{
		skipquotes(&promt, &i);
		passwords(&promt, &i);
		if(promt[i] && promt[i] == '<')
		{
			i++;
			if(promt[i] && promt[i] == '<')
			{
				doc_count++;
				i++;
				while(promt[i] && promt[i] == 32)
					i++;
				if(promt[i] == '\0' || promt[i] == '|' || promt[i] == '<' || promt[i] == '>')
				{
					printf("sytax error\n");
					return(1);
				}
			}
		}
		i++;
	}
	write_docs(promt, doc_count, pars);
	return(0);
}
*/





int	main(void)
{
	char	*promt;
	t_pars	**pars;
	int		i;
	int		count;

	i = 0;
	promt = readline("Minishell ");
	if (!promt)
		return (0);
	if (not_found_second_quote(promt))
	{
		printf("Quote error\n");
		return (0);
	}
	if(check_pipes_count(&promt, &count))
	{
		printf("Pipe error---%d\n", count);
		return(0);
	}
	pars =(t_pars **)malloc(sizeof(t_pars *) * (count));
	pars[count] = NULL;
	while(i < count)
	{
		pars[i] = (t_pars *)malloc(sizeof(t_pars));
		pars[i]->errfile = NULL;
		i++;
	}
	if(openheredoc(promt, pars)) // heredocery stexic a bacum
		return(0);

	i = 0;

















	if (!lexer(&promt, &pars, '<'))
		return (0);
while(i < count)
{
	printf("isheredoc -- %d\n", pars[i]->isheredoc);
	printf("fileordoc == %d\n", pars[i]->fileordoc);
	printf("infile fd --%d\n", pars[i]->infilefd);
	if(pars[i]->errfile)
		printf("errfile --%s\n",pars[i]->errfile);
	i++;
}
//	if (!lexer(&promt, &pars.outfiles, '>'))
//		return (0);
/*	while (pars.infiles && pars.infiles[i])
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
	}*/
//	printf("%s\n%d\n", promt, count);
	return (0);
}
//	printf("%s\n", promt);*/
/*	char *a = "barev dzez vonceq";
	printf("%s\n",ft_trim_substr(&a, 6, 10));
	printf("%s\n",a);*/
//	while(1);
