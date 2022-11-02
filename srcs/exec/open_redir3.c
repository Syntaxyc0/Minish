/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:31:55 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/02 13:48:51 by ggobert          ###   ########.fr       */
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
