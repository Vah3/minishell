/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:21:20 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/12 15:33:06 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	free_and_exit(t_env *env_, char **env)
{
	printf("exit\n");
	free_after_split(env);
	free_env_(&env_);
	set_term_attr(1);
	exit (g_status);
}

int	free_and_close(int (*fd)[2], int count, t_pars **pars, pid_t *id)
{
	close_pipes(fd, count);
	fr(pars, fd, id, count);
	return (1);
}
