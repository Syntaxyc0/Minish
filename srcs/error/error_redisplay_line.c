#include "minishell.h"

int	error_redisplay_line(char *msg, char *token, int errcode)
{
	write_error_message(msg);
	write_error_message(token);
	g_exit_status = errcode;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return  (1);
}