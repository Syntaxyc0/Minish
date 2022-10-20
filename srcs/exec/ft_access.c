/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:57:17 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/20 16:23:58 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_access(t_command *cmd, t_mini *mini)
{
	int		i;
	char	*tmp;
	char	*path;

	i = -1;
	while (mini->all_path[++i])
	{
		tmp = ft_strjoin(mini->all_path[i], "/");
		path = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
				cmd->fullpath = path;
				return (0);
		}
		free(path);
	}
	if (access(cmd->args[0], X_OK) == 0)
		return (0);
	if (!mini->all_path)
		return (-1);
	return (0);
}