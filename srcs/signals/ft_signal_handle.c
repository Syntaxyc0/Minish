/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:01:57 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/24 16:01:58 by jbesnier         ###   ########.fr       */
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

void	ft_handle_exit(t_mini *mini)
{
	free_mini(mini);
	printf("exit\n");
	exit(g_exit_status);
}
