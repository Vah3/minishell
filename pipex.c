/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:47:43 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/12 15:19:23 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_path_rest(char **path, int i)
{
	while (path && path[i])
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
	while (path && path[i] && finaly[1])
	{
		*command = ft_strjoin(path[i++], finaly);
		if (access(*command, F_OK) == 0)
			break ;
		free(*command);
		*command = NULL;
	}
	free_path_rest(path, i);
	free (finaly);
	if (!path)
		*command = NULL;
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
	if (access(command, F_OK) == 0)
		return ;
	slash = ft_strdup("/");
	command = ft_strjoin(slash, *cmd);
	free(*cmd);
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (env[i])
		newenv = ft_split(env[i] + 5, ':');
	check_cmd(&command, newenv);
	*cmd = command;
}
