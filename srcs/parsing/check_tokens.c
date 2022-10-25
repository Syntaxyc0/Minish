/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:47:48 by jbesnier          #+#    #+#             */
/*   Updated: 2022/09/27 16:47:51 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_token(t_mini *mini, t_token *token)
{
	t_token	*tmp;

	tmp = mini->tokens;
	if (tmp == token)
	{
		mini->tokens = tmp->next;
		free(token->value);
		free(token);
		return ;
	}
	while (tmp->next != NULL)
	{
		if (tmp->next == token)
		{
			tmp->next = token->next;
			free(token->value);
			free(token);
			token = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

int	check_redirin(t_mini *mini, t_token *token)
{
	if (token->next == NULL)
		return (0);
	else if (ft_strncmp(token->next->value, ">", 2) == 0)
		return (0);
	else if (ft_strncmp(token->next->value, "<", 2) == 0)
	{
		if (!handle_heredoc(mini, token))
			return (0);
	}
	else if (ft_strncmp(token->next->value, " ", 2) == 0)
	{
		if (token->next->next == NULL)
			return (0);
		if (ft_strncmp(token->next->next->value, "<", 2) == 0)
			return (0);
		if (ft_strncmp(token->next->next->value, ">", 2) == 0)
			return (0);
	}
	return (1);
}

int	check_redirout(t_mini *mini, t_token *token)
{
	if (token->next == NULL)
		return (0);
	if (ft_strncmp(token->next->value, "<", 2) == 0)
		return (0);
	else if (ft_strncmp(token->next->value, ">", 2) == 0)
	{
		if (!handle_append(mini, token))
			return (0);
	}
	else if (ft_strncmp(token->next->value, " ", 2) == 0)
	{
		if (token->next->next == NULL)
			return (0);
		if (ft_strncmp(token->next->next->value, "<", 2) == 0)
			return (0);
		if (ft_strncmp(token->next->next->value, ">", 2) == 0)
			return (0);
	}
	return (1);
}

int	check_redir_syntax(t_mini *mini, t_token *tokens)
{
	if (ft_strncmp(tokens->value, " ", 2) == 0)
	{
		delete_token(mini, tokens);
		tokens = mini->tokens;
	}
	else if (ft_strncmp(tokens->value, "|", 2) == 0)
	{
		if (tokens->next == NULL
			|| ft_strncmp(tokens->next->value, "|", 2) == 0)
			return (error_redisplay_line(ERR_SYNTAX, "'|'", 2));
	}
	else if (ft_strncmp(tokens->value, "<", 2) == 0)
	{
		if (!check_redirin(mini, tokens))
			return (error_redisplay_line(ERR_SYNTAX, "'<'", 2));
	}
	else if (ft_strncmp(tokens->value, ">", 2) == 0)
	{
		if (!check_redirout(mini, tokens))
			return (error_redisplay_line(ERR_SYNTAX, "'>'", 2));
	}
	return (0);
}

int	check_tokens(t_mini *mini)
{
	t_token	*tokens;

	tokens = mini->tokens;
	while (tokens != NULL)
	{
		if (check_redir_syntax(mini, tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
