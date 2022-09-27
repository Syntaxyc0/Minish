/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:56:53 by jbesnier          #+#    #+#             */
/*   Updated: 2022/09/27 16:56:54 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_quote(char *str, int i)
{
	char	quote;
	int		len;

	quote = str[i];
	len = 1;
	while (str[i + len] && str[i + len] != quote)
		len++;
	return (len);
}

int	check_quote_syntax(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}
