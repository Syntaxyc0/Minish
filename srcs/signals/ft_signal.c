/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:21:55 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/09 13:15:57 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	heredoc_c(int signal)
{
	(void)signal;
	g_exit_status = -1;
	close(STDIN_FILENO);
}

void	sigint_process(int signal)
{
	printf("\n");
	(void)signal;
}

void	sigquit_process(int signal)
{
	printf("Quit\n");
	(void)signal;
}

void	signals_process(void)
{
	signal(SIGINT, sigint_process);
	signal(SIGQUIT, sigquit_process);
}
