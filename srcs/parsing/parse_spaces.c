/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:22:16 by jbesnier          #+#    #+#             */
/*   Updated: 2022/09/29 17:22:18 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_space(t_token *token)
{
	int	i;
	char	*str;

	str = token->value;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += len_quote(str, i);
		else if (str[i] == '\"')
			i += len_quote(str, i);
		else if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_only_space(t_token *token, int start)
{
	int	i;
	char	*str;

	str = token->value;
	i = start;
	while (str[i] && str[i] == ' ')
	{
		if (str[i] == '\"')
			i++;
		if (str[i])
			i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
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
	while (token->value[end] != ' ' && token->value[end])
	{
		if (token->value[end] == '\'')
			end += len_quote(token->value, end);
		else if (token->value[end] == '\"')
			end += len_quote(token->value, end);
		else
		{
			if (token->value[end])
				end++;
		}
	}
	ret = ft_substr(token->value, start, end - start);
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	tmp = replace_string(token->value, NULL, 0, end - 1);
	if (!tmp)
		free_mini_exit_msg(mini, ERR_MALLOC);
	token->value = ret;
	return (tmp);
}

int	get_token_value(t_mini *mini, t_token *token)
{
	char	*value;
	t_token	*new;

	value = split_token(mini, token);
	if (value[0] == '\0')
	{
		free(value);
		return (1);
	}
	new = create_token(value);
	new->type = WORD;
	new->next = token->next;
	token->next = new;
	return (0);
}

void	parse_spaces(t_mini *mini)
{
	t_token	*token;
	t_token	*new;

	token = mini->tokens;
	while (token != NULL)
	{
		while (contains_space(token))
		{
			if (check_only_space(token, 0))
			{
				new = token->next;
				delete_token(mini, token);
				token = new;
				if (!token)
					break ;
				continue ;
			}
			if (get_token_value(mini, token))
				break ;
		}
		if (token)
			token = token->next;
	}
	return ;
}
