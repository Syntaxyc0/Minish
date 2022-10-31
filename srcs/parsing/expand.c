/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:58:41 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/31 14:58:42 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_quotes(t_mini *mini, t_token *token, int *i)
{
	token->value = replace_string(token->value, NULL,
			*i + len_quote(token->value, *i + 1) + 1,
			*i + len_quote(token->value, *i + 1) + 1);
	token->value = replace_string(token->value, NULL, *i, *i + 1);
	if (!token->value)
		free_mini_exit_msg(mini, ERR_MALLOC);
}

void	get_err_status(t_mini *mini, t_token *token, int *i)
{
	char	*tmp;

	tmp = ft_itoa(g_exit_status);
	if (!tmp)
		free_mini_exit_msg(mini, ERR_MALLOC);
	token->value = replace_string(token->value, tmp, *i, *i + 1);
	free(tmp);
	if (!token->value)
		free_mini_exit_msg(mini, ERR_MALLOC);
}

int	expand(t_mini *mini, t_token *token, int i)
{
	if (token->value[i + 1] == '\0')
		return (1);
	else if (token->value[i + 1] == '\'' || token->value[i + 1] == '\"')
		replace_quotes(mini, token, &i);
	else if (token->value[i + 1] == '?')
		get_err_status(mini, token, &i);
	else if (ft_isdigit(token->value[i + 1]))
	{
		token->value = replace_string(token->value, NULL, i, i + 1);
		if (!token->value)
			free_mini_exit_msg(mini, ERR_MALLOC);
	}
	else if (ft_isalpha(token->value[i + 1]) || token->value[i + 1] == '_')
		expand_env(mini, token, i);
	else
		return (error_redisplay_line(ERR_SYNTAX, "'$'", 2));
	return (0);
}
