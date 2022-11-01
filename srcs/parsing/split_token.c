/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:46:12 by jbesnier          #+#    #+#             */
/*   Updated: 2022/11/01 10:46:14 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	step_through_token(t_token *token, int end)
{
	while (token->value[end] != ' ' && token->value[end])
	{
		if (token->value[end] == ';')
			end += 2;
		else if (token->value[end] == '\'')
			end += len_quote(token->value, end);
		else if (token->value[end] == '\"')
			end += len_quote(token->value, end);
		else
		{
			if (token->value[end])
				end++;
		}
	}
	return (end);
}

char	*split_token(t_mini *mini, t_token *token)
{
	int		end;
	char	*ret;
	char	*tmp;
	int		start;

	start = 0;
	end = 0;
	while (token->value[start] == ' ' && token->value[start])
		start ++;
	end = start;
	end = step_through_token(token, end);
	ret = ft_substr(token->value, start, end - start);
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	tmp = replace_string(token->value, NULL, 0, end - 1);
	if (!tmp)
		free_mini_exit_msg(mini, ERR_MALLOC);
	token->value = ret;
	return (tmp);
}
