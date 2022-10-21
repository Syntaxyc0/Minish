#include "minishell.h"

int	error_redisplay_line(char *msg, char *token, int errcode)
{
	write_error_message(msg);
	write_error_message(token);
	g_exit_status = errcode;
	return (1);
}