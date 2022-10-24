#include "minishell.h"

void	ft_sigint_handle(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	ft_sigint_process_handle(void)
{
	struct sigaction	sa1;

	sa1.sa_handler = ft_kill_proc;
	sigemptyset(&sa1.sa_mask);
	sa1.sa_flags = 0;
	sigaction(SIGINT, &sa1, NULL);
}

void	ft_handle_exit(t_mini *mini)
{
	free_mini(mini);
	printf("exit\n");
	exit(g_exit_status);
}