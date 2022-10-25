/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:26:31 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/25 11:26:31 by ggobert          ###   ########.fr       */
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

int	exit_perror(int ges, int ret)
{
	g_exit_status = ges;
	perror(NULL);
	if (ret == -1)
		return (-1);
	return (0);
}