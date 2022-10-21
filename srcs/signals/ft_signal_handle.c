#include "minishell.h"

void	ft_sigint_handle(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_signal;
	sigaction(SIGINT, &sa, NULL);
}

void	ft_handle_exit(t_mini *mini)
{
	free_mini(mini);
	printf("exit\n");
	exit(g_exit_status);
}