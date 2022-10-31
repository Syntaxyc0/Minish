/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_markers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:08:53 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/31 14:08:55 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_marker(char *str, int start)
{
	int	i;

	if (start < 0)
		return (0);
	i = start;
	while (str[i])
	{
		if (str[i] == ';')
			return (i);
		i++;
	}
	return (-1);
}

int	remove_markers(t_mini *mini)
{
	t_token	*token;
	int		start;

	start = 0;
	token = mini->tokens;
	while (token != NULL)
	{
		if (token->type == WORD)
		{
			start = contains_marker(token->value, 0);
			while (start != -1)
			{
				token->value = replace_string(token->value, NULL, start, start);
				if (!token->value)
					free_mini_exit_msg(mini, ERR_MALLOC);
				start = contains_marker(token->value, 0);
			}
		}
		token = token->next;
	}
	return (0);
}
