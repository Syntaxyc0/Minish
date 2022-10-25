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
	char	*ret;

	i = 256;
	ret = malloc(i);
	if (!ret)
	{
		g_exit_status = 1;
		free_mini_exit_msg(mini, ERR_MALLOC);
	}
	path = pwd_get_cwd(mini, i, ret);
	if (any_redir_out(cmd))
		write(cmd->fd[1], path, ft_strlen(path));
	else
		printf("%s\n", path);
	if (errno == ERANGE)
		free(path);
}

char	*pwd_get_cwd(t_mini *mini, int i, char *ret)
{
	while (getcwd(ret, i) == 0)
	{
		if (errno == EACCES || errno == ENOENT)
		{
			ret = NULL;
			ret = get_env_value(mini, "PWD");
			return (ret);
		}
		if (errno == ERANGE)
		{
			i *= 2;
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
