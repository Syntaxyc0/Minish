/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:36 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/24 16:23:07 by ggobert          ###   ########.fr       */
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

void	ft_handle_exit(t_mini *mini)
{
	free_mini(mini);
	write_error_message("exit\n");
	exit(g_exit_status);
}
