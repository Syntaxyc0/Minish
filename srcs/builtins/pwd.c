/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:38:35 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/01 11:37:25 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_command *cmd, t_mini *mini)
{
	int		i;
	char	*path;
	char	*ret;

	g_exit_status = 0;
	i = 256;
	ret = malloc(i);
	if (!ret)
	{
		g_exit_status = 1;
		free_mini_exit_msg(mini, ERR_MALLOC);
	}
	path = pwd_get_cwd(mini, i, ret);
	if (any_redir_out(cmd) && cmd_len(mini) == 1)
	{
		write(cmd->fd[1], path, ft_strlen(path));
		write(cmd->fd[1], "\n", 1);
	}
	else
		printf("%s\n", path);
	free(path);
}

char	*pwd_get_cwd(t_mini *mini, int i, char *ret)
{
	while (getcwd(ret, i) == 0)
	{
		if (errno == EACCES || errno == ENOENT)
		{
			free(ret);
			ret = NULL;
			ret = ft_strdup(get_env_value(mini, "PWD"));
			return (ret);
		}
		if (errno == ERANGE)
		{
			i *= 2;
			free(ret);
			ret = NULL;
			ret = malloc(i);
			if (!ret)
			{
				g_exit_status = 1;
				free_mini_exit_msg(mini, ERR_MALLOC);
			}
		}
	}
	return (ret);
}
