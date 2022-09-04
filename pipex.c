/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:47:43 by vagevorg          #+#    #+#             */
/*   Updated: 2022/09/04 16:31:11 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_cmd(char	**command, char **env)
{
	char	*finaly;
	int		i;

	i = 0;
	finaly = *command;
	while (env[i] && access(*command, X_OK) != 0)
	{
		*command = ft_strjoin(env[i++], finaly);
		if (access(*command, X_OK) != 0)
			free(*command);
	}
	free(finaly);
	if (env[i] == NULL)
	{
		perror("Comomand not found");
		free(env);
		exit(0);
	}
	while(env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
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
