/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:36 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/09 13:33:18 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_handle(void)
{
	struct sigaction	sa[2];

	sa[0].sa_handler = ft_signal;
	sigemptyset(&sa[0].sa_mask);
	sa[0].sa_flags = 0;
	sigaction(SIGINT, &sa[0], NULL);
	sa[1].sa_handler = SIG_IGN;
	sigemptyset(&sa[1].sa_mask);
	sa[1].sa_flags = 0;
	sigaction(SIGQUIT, &sa[1], NULL);
}

void	process_sig_handle(void)
{
	struct sigaction	sac;

	sac.sa_handler = SIG_IGN;
	sigemptyset(&sac.sa_mask);
	sac.sa_flags = 0;
	sigaction(SIGINT, &sac, NULL);
}

void	heredoc_sig_handle(void)
{
	struct sigaction	s;

	s.sa_handler = heredoc_c;
	sigemptyset(&s.sa_mask);
	s.sa_flags = 0;
	sigaction(SIGINT, &s, NULL);
}

void	ft_handle_exit(t_mini *mini)
{
	free_mini(mini);
	write_error_message("exit\n");
	exit(g_exit_status);
}
