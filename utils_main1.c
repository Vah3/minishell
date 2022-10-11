/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:21:20 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/11 15:24:30 by vagevorg         ###   ########.fr       */
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
