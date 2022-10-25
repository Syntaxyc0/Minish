/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_handle_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:45 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/24 16:22:46 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append(t_mini *mini, t_token *token)
{
	char	*tmp;

	if (token->next->next == NULL)
		return (0);
	if (ft_strncmp(token->next->next->value, "<", 2) == 0)
		return (0);
	if (ft_strncmp(token->next->next->value, ">", 2) == 0)
		return (0);
	tmp = ft_strjoin(token->value, token->next->value);
	if (!tmp)
		free_mini_exit_msg(mini, ERR_MALLOC);
	free(token->value);
	token->value = tmp;
	delete_token(mini, token->next);
	return (1);
}

int	handle_heredoc(t_mini *mini, t_token *token)
{
	char	*tmp;

	if (token->next->next == NULL)
		return (0);
	if (ft_strncmp(token->next->next->value, "<", 2) == 0)
		return (0);
	if (ft_strncmp(token->next->next->value, ">", 2) == 0)
		return (0);
	tmp = ft_strjoin(token->value, token->next->value);
	if (!tmp)
		free_mini_exit_msg(mini, ERR_MALLOC);
	free(token->value);
	token->value = tmp;
	delete_token(mini, token->next);
	return (1);
}
