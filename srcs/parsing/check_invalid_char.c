/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:08:12 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/31 14:08:36 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_invalid_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\\')
			return (error_redisplay_line("'\\'", ERR_INVALID, 1));
		else if (input[i] == ';')
			return (error_redisplay_line("';'", ERR_INVALID, 1));
		i++;
	}
	return (0);
}
