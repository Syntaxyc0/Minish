#include "minishell.h"

t_command	*init_cmd(void)
{
	t_command	*ret;

	ret = malloc(sizeof(t_command));
	if (!ret)
		return (NULL);
	ret->red
}

int	parse_cmds(t_mini	*mini)
{
	t_token		*token;
	t_command	*cmd;

	token = mini->tokens;
	mini->commands = init_cmd();

}