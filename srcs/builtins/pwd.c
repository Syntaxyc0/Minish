/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:38:35 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/24 16:21:44 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_command *cmd, t_mini *mini)
{
	int		i;
	char	*path;

	i = 256;
	path = malloc(i);
	if (!path)
	{
		g_exit_status = 1;
		free_mini_exit_msg(mini, ERR_MALLOC);
	}
	pwd_get_cwd(path, i, mini);
	if (any_redir_out(cmd))
		write(cmd->fd[1], path, ft_strlen(path));
	else
		printf("%s\n", path);
	free(path);
}

void	pwd_get_cwd(char *path, int i, t_mini *mini)
{
	while (getcwd(path, i) == 0)
	{
		free(path);
		i *= 2;
		path = malloc(i);
		if (!path)
		{
			g_exit_status = 1;
			free_mini_exit_msg(mini, ERR_MALLOC);
		}
	}
}
