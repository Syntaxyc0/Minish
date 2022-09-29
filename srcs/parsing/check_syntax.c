/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:19:27 by jbesnier          #+#    #+#             */
/*   Updated: 2022/09/29 17:19:32 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_mini *mini)
{
	t_token	*token;

	token = mini->tokens;
	while (token != NULL)
	{
		if (token->type == REDIR)
		{
			if (token->next == NULL)
				return (0);
			if (token->next->type == REDIR)
				return (0);
			if (token->next->type == PIPE)
				return (0);
		}
		if (token->type == PIPE)
		{
			if (token->next == NULL)
				return (0);
			if (token->next->type == PIPE)
				return (0);
		}
		token = token->next;
	}
	return (1);
}
