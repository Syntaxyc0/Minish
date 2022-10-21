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

int	check_redirin_syntax(t_token *token)
{
	if (token->next == NULL)
		return (error_redisplay_line(ERR_SYNTAX, "'<'", 2));
	if (token->next->type == REDIROUT)
		return (error_redisplay_line(ERR_SYNTAX, "'<'", 2));
	if (token->next->type == PIPE)
		return (error_redisplay_line(ERR_SYNTAX, "'<'", 2));
	return (0);
}

int	check_redirout_syntax(t_token *token)
{
	if (token->next == NULL)
		return (error_redisplay_line(ERR_SYNTAX, "'>'", 2));
	if (token->next->type == REDIRIN)
		return (error_redisplay_line(ERR_SYNTAX, "'>'", 2));
	if (token->next->type == PIPE)
		return (error_redisplay_line(ERR_SYNTAX, "'>'", 2));
	return (0);
}

int	check_redirpipe_syntax(t_token *token)
{
	if (token->next == NULL)
		return (error_redisplay_line(ERR_SYNTAX, "'|'", 2));
	if (token->next->type == PIPE)
		return (error_redisplay_line(ERR_SYNTAX, "'|'", 2));
	return (0);
}

int	check_syntax(t_mini *mini)
{
	t_token	*token;

	token = mini->tokens;
	while (token != NULL)
	{
		if (token->type == REDIRIN || token->type == HEREDOC)
		{
			if (check_redirin_syntax(token))
				return (1);
		}
		else if (token->type == REDIROUT || token->type == APPEND)
		{
			if (check_redirout_syntax(token))
				return (1);
		}
		else if (token->type == PIPE)
		{
			if (check_redirpipe_syntax(token))
				return (1);
		}
		token = token->next;
	}
	return (0);
}
