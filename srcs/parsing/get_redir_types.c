/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:21:21 by jbesnier          #+#    #+#             */
/*   Updated: 2022/09/29 17:21:22 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_redir_types(t_mini *mini)
{
	t_token	*token;

	token = mini->tokens;
	while (token != NULL)
	{
		if (!ft_strncmp(token->value, "<<", 3) && token->type == REDIR)
			token->type = HEREDOC;
		else if (!ft_strncmp(token->value, "<", 2) && token->type == REDIR)
			token->type = REDIRIN;
		else if (!ft_strncmp(token->value, ">>", 3) && token->type == REDIR)
			token->type = APPEND;
		else if (!ft_strncmp(token->value, ">", 2) && token->type == REDIR)
			token->type = REDIROUT;
		token = token->next;
	}
}
