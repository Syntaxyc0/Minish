/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:19:01 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/03 11:17:43 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (isdigit(str[i]) == 0)
			return (0);
	return (1);
}

void	ft_exit(t_mini *mini, int ac, char **av)
{
	if (ac > 2)
	{
		write_error_message(ERR_ARG);
		return;
	}
	if (ac == 2)
	{
		if (str_isdigit(av[1]))
		{
			free_mini(mini);
			exit(ft_atoi(av[1]));
		}
		else
		{
			write_error_message("msh : numeric argument required");
			free_mini(mini);
			exit(g_exit_status);
		}
	}
	free_mini(mini);
	exit;
}
