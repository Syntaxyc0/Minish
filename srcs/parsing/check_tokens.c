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
			return ;
		}
		tmp = tmp->next;
	}
}

int	check_redirin(t_mini *mini, t_token *token)
{
	char	*tmp;

	if (token->next == NULL)
		return (0);
	if (ft_strncmp(token->next->value, ">", 2) == 0)
		return (0);
	if (ft_strncmp(token->next->value, "<", 2) == 0)
	{
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
	return (1);
}

int	check_redirout(t_mini *mini, t_token *token)
{
	char	*tmp;

	if (token->next == NULL)
		return (0);
	if (ft_strncmp(token->next->value, "<", 2) == 0)
		return (0);
	if (ft_strncmp(token->next->value, ">", 2) == 0)
	{
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
	return (1);
}

void	check_tokens(t_mini *mini)
{
	t_token	*tokens;

	tokens = mini->tokens;
	while (tokens != NULL)
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
				free_mini_exit_msg(mini, ERR_SYNTAX);
		}
		else if (ft_strncmp(tokens->value, "<", 2) == 0)
		{
			if (!check_redirin(mini, tokens))
				free_mini_exit_msg(mini, ERR_SYNTAX);
		}
		else if (ft_strncmp(tokens->value, ">", 2) == 0)
		{
			if (!check_redirout(mini, tokens))
				free_mini_exit_msg(mini, ERR_SYNTAX);
		}
		tokens = tokens->next;
	}
}
