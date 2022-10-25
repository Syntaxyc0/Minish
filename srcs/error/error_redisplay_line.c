/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redisplay_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:57:14 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/24 15:57:15 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_redisplay_line(char *msg, char *token, int errcode)
{
	write_error_message(msg);
	write_error_message(token);
	g_exit_status = errcode;
	return (1);
}
