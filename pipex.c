/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:47:43 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/05 10:14:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_cmd(char	**command, char **path)
{
	char	*finaly;
	int		i;

	i = 0;
	finaly = *command;
	while (path[i])
	{
		*command = ft_strjoin(path[i++], finaly);
		if (access(*command, X_OK) == 0)
			break ;
		if (access(*command, X_OK) != 0)
			free(*command);
	}
	free(finaly);
	if (path[i] == NULL)
	{
		perror("Comomand not found");
		free(path);
		exit(0);
	}
	while (path[i])
		free(path[i++]);
	free(path);
}

void	check_make(char **cmd, char **env)
{
	char	*command;
	char	*slash;
	char	**newenv;
	int		i;

	i = 0;
	command = *cmd;
	if (access(command, X_OK) == 0)
		return ;
	slash = ft_strdup("/");
	command = ft_strjoin(slash, *cmd);
	free(*cmd);
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	newenv = ft_split(env[i] + 5, ':');
	i = 0;
	check_cmd(&command, newenv);
	*cmd = command;
}
