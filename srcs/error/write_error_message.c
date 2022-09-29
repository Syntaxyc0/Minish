#include "minishell.h"

int	write_error_message(char *message)
{
	write(2, message, ft_strlen(message));
	return (1);
}