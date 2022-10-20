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
		if (token->type == REDIRIN || token->type == HEREDOC)
		{
			if (token->next == NULL)
				return (error_redisplay_line(ERR_SYNTAX, "'<'", 2));
			if (token->next->type == REDIROUT)
				return (error_redisplay_line(ERR_SYNTAX, "'<'", 2));
			if (token->next->type == PIPE)
				return (error_redisplay_line(ERR_SYNTAX, "'<'", 2));
		}
		else if (token->type == REDIROUT ||  token->type == APPEND)
		{
			if (token->next == NULL)
				return (error_redisplay_line(ERR_SYNTAX, "'>'", 2));
			if (token->next->type == REDIRIN)
				return (error_redisplay_line(ERR_SYNTAX, "'>'", 2));
			if (token->next->type == PIPE)
				return (error_redisplay_line(ERR_SYNTAX, "'>'", 2));
		}
		else if (token->type == PIPE)
		{
			if (token->next == NULL)
				return (error_redisplay_line(ERR_SYNTAX, "'|'", 2));
			if (token->next->type == PIPE)
				return (error_redisplay_line(ERR_SYNTAX, "'|'", 2));
		}
		token = token->next;
	}
	return (0);
}
