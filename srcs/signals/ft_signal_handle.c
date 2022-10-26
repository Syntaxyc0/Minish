/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:36 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/26 15:30:50 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_handle(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	process_sig_handle(void)
{
	struct sigaction	sac[2];

	sac[0].sa_handler = SIG_IGN;
	sigemptyset(&sac[0].sa_mask);
	sac[0].sa_flags = 0;
	sigaction(SIGINT, &sac[0], NULL);
	sac[1].sa_handler = SIG_IGN;
	sigemptyset(&sac[1].sa_mask);
	sac[1].sa_flags = 0;
	sigaction(SIGQUIT, &sac[1], NULL);
}

void	heredoc_sig_handle(void)
{
	struct sigaction	s[2];

	s[0].sa_handler = heredoc_C;
	sigemptyset(&s[0].sa_mask);
	s[0].sa_flags = 0;
	sigaction(SIGINT, &s[0], NULL);
	s[1].sa_handler = heredoc_D;
	sigemptyset(&s[1].sa_mask);
	s[1].sa_flags = 0;
	sigaction(SIGQUIT, &s[1], NULL);
}

void	ft_handle_exit(t_mini *mini)
{
	free_mini(mini);
	write_error_message("exit\n");
	exit(g_exit_status);
}
