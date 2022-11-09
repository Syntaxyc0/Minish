/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:22:37 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/09 10:49:39 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;
	char	*line;

	g_exit_status = 0;
	mini = init_mini();
	get_env(env, mini);
	(void)argc;
	(void)argv;
	while (1)
	{
		ft_sigint_handle(mini);
		line = readline(MINI);
		if (!line)
			ft_handle_exit(mini);
		else
			add_history(line);
		if (parser(mini, line))
			continue ;
		if (exec(mini) == -1)
			return (error_mini(mini));
		free_commands(mini);
		free(line);
	}
	free_mini(mini);
	return (0);
}
