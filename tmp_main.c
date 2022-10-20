#include "minishell.h"


int	g_exit_status;

int main(int argc, char **argv, char **env)
{
	t_mini *mini;
	char	*line;

	g_exit_status = 0;
	mini = init_mini();
	get_env(env, mini);
	(void)argc;
	(void)argv;
	while(1)
	{
		line = readline("Minishell: ");
		if (!line)
			break;
		parse_token(mini, line);
		if (check_tokens(mini))
			free_tokens(mini);
		get_redir_types(mini);
		if (check_syntax(mini))
			free_tokens(mini);
		parse_spaces(mini);
		expander(mini);
		parse_spaces(mini);
		if (remove_quotes(mini))
			free_mini_exit_msg(mini, ERR_MALLOC);
		if (parse_exec_form(mini))
			free_mini_exit_msg(mini, NULL);
		exec(mini);
		if (line)
			add_history(line);
		free_commands(mini);
	}
	free_mini(mini);
}