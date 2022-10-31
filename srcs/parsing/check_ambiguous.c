/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:39:10 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/31 13:40:55 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_contains_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		else
			i++;
	}
	return (0);
}

int	expand_len(char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != '\''
		&& str[i + j] != '\"' && str[i + j] != '$'
		&& str[i + j] != ' ')
		j++;
	return (j);
}

char	*get_substr(t_mini *mini, char *str, int *i, int *j)
{
	char	*ret;

	*j = expand_len(str, *i);
	ret = ft_substr(str, *i + 1, *j - 1);
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	return (ret);
}

int	exp_contains_space(t_mini *mini, char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += len_quote(str, i);
		else if (str[i] == '$')
		{
			tmp = get_substr(mini, str, &i, &j);
			value = get_env_value(mini, tmp);
			free(tmp);
			if (str_contains_space(value))
				return (1);
			i += j;
		}
		else
			i++;
	}
	return (0);
}

int	check_expandredirs(t_mini *mini)
{
	t_token	*token;

	token = mini->tokens;
	while (token != NULL)
	{
		if (token->type == REDIR && token->next && token->next->type == WORD)
		{
			if (contains_exp_sign(token->next->value) != -1)
			{
				if (exp_contains_space(mini, token->next->value))
					return (error_redisplay_line(token->next->value,
							ERR_AMBI, 1));
			}
		}
		token = token->next;
	}
	return (0);
}
