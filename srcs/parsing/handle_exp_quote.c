/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exp_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:55:04 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/31 13:55:18 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_contains_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';')
			i++;
		else if (str[i] == '\'' || str[i] == '\"')
			return (i);
		i++;
	}
	return (-1);
}

char	*add_symbol_before(char *str, int i, int *free1)
{
	char	*ret;
	char	*tmp;
	char	*cpy;

	cpy = ft_strdup(str);
	if (!cpy)
		return (NULL);
	if (*free1)
		free(str);
	if (i == 0)
	{
		ret = ft_strjoin(";", cpy);
		if (!ret)
		{
			free(cpy);
			return (NULL);
		}
	}
	else
	{
		ret = ft_substr(cpy, 0, i);
		if (!ret)
		{
			free(cpy);
			return (NULL);
		}
		tmp = ft_substr(cpy, i, ft_strlen(cpy));
		if (!cpy)
		{
			free(ret);
			free(cpy);
			return (NULL);
		}
		ret = ft_strjoin_free(ret, ";", 1, 0);
		if (!ret)
		{
			free(tmp);
			free(cpy);
			return (NULL);
		}
		ret = ft_strjoin_free(ret, tmp, 1, 1);
		if (!ret)
		{
			free(cpy);
			return (NULL);
		}
	}
	free(cpy);
	return (ret);
}

char	*handle_exp_quote(t_mini *mini, char *str, int *free1)
{
	int		i;
	char	*ret;

	i = exp_contains_quote(str);
	ret = str;
	while (i != -1)
	{
		ret = add_symbol_before(ret, i, free1);
		if (!ret)
			free_mini_exit_msg(mini, ERR_MALLOC);
		*free1 = 1;
		i = exp_contains_quote(ret);
	}
	return (ret);
}
