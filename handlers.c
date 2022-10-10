#include "minishell.h"
extern int g_status;

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