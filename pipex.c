/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgghaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:47:43 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/20 16:35:02 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_and_exit(char *for_print, char *finaly, int code)
{
	printf("%s: %s\n", (finaly + 1), for_print);
	free(finaly);
	exit(code);
}

static int	free_path_rest(char **path, int i)
{
	while (path[i])
		free(path[i++]);
	free(path);
	return (1);
}

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
	if (opendir(finaly + 1) && free_path_rest(path, i))
		free_and_exit("is a directory", finaly, 126);
	else if (ft_strchr(finaly + 1, '/')
		&& (access((finaly + 1), F_OK) == -1) && free_path_rest(path, i))
		free_and_exit("No such file or directory", finaly, 127);
	if (((!path || path[i] == NULL)
			&& (access((finaly + 1), F_OK) == -1)))
		free_and_exit("Comomand not found", finaly, 127);
	if ((!path || path[i] == NULL) && access((finaly + 1), F_OK) == 0)
		free_and_exit("Permission denied", finaly, 126);
	free_path_rest(path, i);
	free (finaly);
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
