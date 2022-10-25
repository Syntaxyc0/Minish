#include "minishell.h"

//Il est plus beau comme ca hein ??!
// Bon j'ai pas encore mis l'exec
// putain de norminette..

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
		ft_sigint_handle();
		line = readline(MINI);
		if (!line)
			ft_handle_exit(mini);
		else
			add_history(line);
		if (parser(mini, line))
			continue ;
		if (exec(mini) == -1)
		{
			free_mini(mini);
			return (1);
		}
		free(line);
		line = NULL;
		free_commands(mini);
	}
	free_mini(mini);
	return (0);
}