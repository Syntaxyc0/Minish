/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:31:55 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/09 13:48:01 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_tmp_add(t_mini *mini, char *str)
{
	char	*path_tmp;

	path_tmp = ft_strjoin_free("/tmp/", str, 0, 1);
	if (!path_tmp)
		exit_free_status_msg(mini, 1, ERR_MALLOC);
	return (path_tmp);
}

int	norminette_command(t_mini *mini)
{
	heredoc_annihilator(mini);
	g_exit_status = 130;
	return (-1);
}

void	norminette_command2(t_mini *mini, char *line)
{
	free(line);
	exit_free_status_msg(mini, 0,
		"warning : here-document delimited by end-of-file\n");
}
