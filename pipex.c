/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:47:43 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/18 15:44:26 by edgghaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_cmd(char	**command, char **path)
{
	char	*finaly;
	int		i;

	i = 0;
	finaly = *command;
	while (path && path[i])
	{
		*command = ft_strjoin(path[i++], finaly);
		if (access(*command, X_OK) == 0)
			break ;
		if (access(*command, X_OK) != 0)
			free(*command);
	}
	if (opendir(finaly + 1))
	{
		printf("%s: is a directory\n", (finaly + 1));
		free(path);
		free(finaly);
		exit(126);
	}
	else if (ft_strchr(finaly +1, '/') && access((finaly + 1), F_OK) == -1)
	{
		printf("%s: No such file or directory\n", (finaly + 1));
		free(path);
		free(finaly);
		exit(127);
	}
	if (((!path || path[i] == NULL)
			&& (access((finaly + 1), F_OK) == -1)))
	{
		printf("%s: Comomand not found\n", (finaly + 1));
		free(path);
		free(finaly);
		exit(127);
	}
	if ((!path || path[i] == NULL) && access((finaly + 1), F_OK) == 0)
	{
		printf("%s: Permission denied\n", (finaly + 1));
		free(path);
		free(finaly);
		exit(126);
	}
	free(finaly);
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

	newenv = NULL;
	i = 0;
	command = *cmd;
	if (!opendir(command) && access(command, X_OK) == 0)
		return ;
	slash = ft_strdup("/");
	command = ft_strjoin(slash, *cmd);
	free(*cmd);
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (env[i])
		newenv = ft_split(env[i] + 5, ':');
	i = 0;
	check_cmd(&command, newenv);
	*cmd = command;
}
