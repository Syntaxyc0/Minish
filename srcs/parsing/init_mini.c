#include "minishell.h"

t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
	{
		write_error_message(ERR_MALLOC);
		exit (1);
	}
    mini->myenv = NULL;
	mini->myexport = NULL;
	mini->tokens = NULL;
	return (mini);
}