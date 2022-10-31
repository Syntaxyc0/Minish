/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:55:32 by jbesnier          #+#    #+#             */
/*   Updated: 2022/09/27 16:55:33 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_exp_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';')
			i += 2;
		else if (str[i] == '\'')
			i += len_quote(str, i);
		else if (str[i] == '\"')
			i++;
		else if (str[i] == '$')
			return (i);
		else
			i++;
	}
	return (-1);
}

void	expand_env(t_mini *mini, t_token *token, int i)
{
	char	*tmp;
	char	*ret;
	int		j;
	int		free1;

	j = 1;
	free1 = 0;
	while (token->value[i + j] && token->value[i + j] != '\''
		&& token->value[i + j] != '\"' && token->value[i + j] != '$'
		&& token->value[i + j] != ' ')
		j++;
	tmp = ft_substr(token->value, i + 1, j - 1);
	if (!tmp)
		free_mini_exit_msg(mini, ERR_MALLOC);
	ret = get_env_value(mini, tmp);
	free(tmp);
	if (!ret)
	{
		token->value = replace_string(token->value, NULL, i, i + j - 1);
		if (!token->value)
			free_mini_exit_msg(mini, ERR_MALLOC);
		return ;
	}
	else
		ret = handle_exp_quote(mini, ret, &free1);
	token->value = replace_string(token->value, ret, i, i + j - 1);
	if (free1)
		free(ret);
	if (!token->value)
		free_mini_exit_msg(mini, ERR_MALLOC);
	return ;
}

int	expander(t_mini *mini)
{
	t_token	*token;
	t_token	*tmp;
	int		index;

	token = mini->tokens;
	if (mini->tokens == NULL)
		return (error_redisplay_line(NULL, NULL, 0));
	while (token != NULL)
	{
		index = contains_exp_sign(token->value);
		while (index != -1)
		{
			if (index >= 0)
			{
				if (expand(mini, token, index))
					return (1);
			}
			if (token->value[0] == 0)
			{
				tmp = token->next;
				delete_token(mini, token);
				token = tmp;
				if (!token)
					break ;
			}
			index = contains_exp_sign(token->value);
		}
		if (token)
			token = token->next;
	}
	return (0);
}
