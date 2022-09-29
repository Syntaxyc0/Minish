/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:25:03 by jbesnier          #+#    #+#             */
/*   Updated: 2022/09/28 11:25:05 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(char	*str)
{
	if (*str == '<' || *str == '>')
		return (REDIR);
	else if (*str == '|')
		return (PIPE);
	else
		return (WORD);
}

void	get_token_type(t_mini *mini)
{
	t_token *token;

	token = mini->tokens;
	while (token != NULL)
	{
		token->type = get_type(token->value);
		token = token->next;
	}
	return ;
}
