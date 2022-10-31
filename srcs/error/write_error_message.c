/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:57:23 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/24 15:57:25 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_error_message(char *message)
{
	if (!message)
		return (1);
	write(2, message, ft_strlen(message));
	return (1);
}

int	return_perror(int ges, int ret)
{
	g_exit_status = ges;
	perror(NULL);
	if (ret == -1)
		return (-1);
	return (0);
}

void	exit_perror(int ges)
{
	perror(NULL);
	exit(ges);
}
