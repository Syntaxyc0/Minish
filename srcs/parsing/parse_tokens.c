/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:44:45 by jbesnier          #+#    #+#             */
/*   Updated: 2022/09/27 16:44:48 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value)
{
	t_token	*ret;

	ret = malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->value = value;
	ret->type = 0;
	ret->next = NULL;
	return (ret);
}

void	addback_token(t_mini *mini, t_token *token)
{
	t_token	*tmp;

	tmp = mini->tokens;
	if (tmp == NULL)
	{
		mini->tokens = token;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = token;
}

void	add_token(t_mini *mini, char *str, int *start, int *i)
{
	char	*ret;
	t_token	*token;

	if (*i != *start)
	{
		ret = ft_substr(str, *start, *i - *start);
		if (!ret)
			free_mini_exit_msg(mini, ERR_MALLOC);
		token = create_token(ret);
		addback_token(mini, token);
		*start = *i;
	}
	*i += 1;
	ret = ft_substr(str, *start, *i - *start);
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	token = create_token(ret);
	if (!token)
		free_mini_exit_msg(mini, ERR_MALLOC);
	addback_token(mini, token);
	*start = *i;
}

void	parse_substr(t_mini *mini, char *str, int *start, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '"')
			*i += len_quote(str, *i) + 1;
		else if (str[*i] == '<' || str[*i] == '>'
			|| str[*i] == '|' || str[*i] == ' ')
			add_token(mini, str, start, i);
		else
			*i += 1;
	}
}

int	parse_token(t_mini *mini, char *str)
{
	int		i;
	int		start;
	t_token	*token;
	char	*ret;

	i = 0;
	start = 0;
	if (str[i] == 0)
		return (1);
	if (!check_quote_syntax(str))
		return (error_redisplay_line(ERR_QUOTES, NULL, 1));
	parse_substr(mini, str, &start, &i);
	if (i != start)
	{
		ret = ft_substr(str, start, i - start);
		if (!ret)
			free_mini_exit_msg(mini, ERR_MALLOC);
		token = create_token(ret);
		addback_token(mini, token);
	}
	get_token_type(mini);
	return (0);
}
