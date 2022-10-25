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
		if (str[i] == '\'')
			i += len_quote(str, i);
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

	j = 1;
	while (token->value[i + j] && token->value[i + j] != '\''
		&& token->value[i + j] != '\"' && token->value[i + j] != '$'
		&& token->value[i + j] != ' ')
		j++;
	tmp = ft_substr(token->value, i + 1, j - 1);
	if (!tmp)
		free_mini_exit_msg(mini, ERR_MALLOC);
	ret = get_env_value(mini, tmp);
	if (!ret)
	{
		free(tmp);
		token->value = replace_string(token->value, NULL, i, i + j - 1);
		if (!token->value)
			free_mini_exit_msg(mini, ERR_MALLOC);
		return ;
	}
	token->value = replace_string(token->value, ret, i, i + j - 1);
	if (!token->value)
		free_mini_exit_msg(mini, ERR_MALLOC);
	token->value = replace_string(token->value, "\"", 0, 0);
	token->value = replace_string(token->value, "\"", ft_strlen(token->value), ft_strlen(token->value));
	free(tmp);
	return ;
}

void	expand(t_mini *mini, t_token *token, int i)
{
	char	*tmp;

	if (token->value[i + 1] == '\0')
		return ;
	else if (token->value[i + 1] == '\'' || token->value[i + 1] == '\"')
	{
		token->value = replace_string(token->value, NULL,
				i + len_quote(token->value, i + 1) + 1,
				i + len_quote(token->value, i + 1) + 1);
		token->value = replace_string(token->value, NULL, i, i + 1);
		if (!token->value)
			free_mini_exit_msg(mini, ERR_MALLOC);
	}
	else if (token->value[i + 1] == '?')
	{
		tmp = ft_itoa(g_exit_status);
		if (!tmp)
			free_mini_exit_msg(mini, ERR_MALLOC);
		token->value = replace_string(token->value, tmp, i, i + 1);
		if (!token->value)
		{
			free(tmp);
			free_mini_exit_msg(mini, ERR_MALLOC);
		}
		free(tmp);
	}
	else if (ft_isdigit(token->value[i + 1]))
	{
		token->value = replace_string(token->value, NULL, i, i + 1);
		if (!token->value)
			free_mini_exit_msg(mini, ERR_MALLOC);
	}
	else if (ft_isalpha(token->value[i + 1]) || token->value[i + 1] == '_')
		expand_env(mini, token, i);
	else
		free_mini_exit_msg(mini, ERR_SYNTAX);
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
				expand(mini, token, index);
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
