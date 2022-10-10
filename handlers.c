/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:58:21 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/10 17:59:59 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	handle4(int i)
{
	(void) i;
	g_status = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle2(int i)
{
	(void) i;
	g_status = -1;
	write(1, "\n", 1);
	close (0);
}

void	handle0(int i)
{
	(void) i;
	g_status = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle1(int i)
{
	(void) i;
	g_status = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
}
