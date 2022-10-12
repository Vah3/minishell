/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:17:54 by vagevorg          #+#    #+#             */
/*   Updated: 2022/10/12 19:05:13 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_term_attr(int on_off)
{
	struct termios	termios_p;

	tcgetattr(0, &termios_p);
	if (on_off == 0)
	{
		termios_p.c_lflag &= ~ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}
	else if (on_off == 1)
	{
		termios_p.c_lflag |= ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}	
}

void	save_std(void)
{
	static int	stdin_;
	static int	stdout_;
	static int	count;

	if (count == 0)
	{
		stdin_ = dup(STDIN_FILENO);
		stdout_ = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(stdin_, STDIN_FILENO);
		dup2(stdout_, STDOUT_FILENO);
	}
	count++;
}

void	set_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

int	fret(t_pars **pars, char *promt, char **env)
{
	free_pars(pars);
	free(promt);
	free_after_split (env);
	return (1);
}

void	set_setting(int gr)
{
	save_std();
	set_term_attr(0);
	if (gr == 0)
		signal(SIGINT, handle0);
}
