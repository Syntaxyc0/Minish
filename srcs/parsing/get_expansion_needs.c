/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expansion_needs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:21:00 by jbesnier          #+#    #+#             */
/*   Updated: 2022/09/29 17:21:02 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_expansion_needs(t_mini *mini)
{
	t_token	*token;

	token = mini->tokens;
	while (token != NULL)
	{
		if (token->type == HEREDOC && token->next->type == WORD)
				token->next->needs_expansion = 0;
		token = token->next;
	}
}
