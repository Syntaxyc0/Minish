/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:52:29 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/24 10:52:32 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_2_str(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (NULL);
}

void	free_replace_string(char *prefix, char *suffix, char *value, char *tmp)
{
	free(prefix);
	free(suffix);
	free(value);
	if (tmp)
		free(tmp);
}

char	*replace_string(char *value, char *str, int start, int end)
{
	char	*ret;
	char	*tmp;
	char	*prefix;
	char	*suffix;

	tmp = NULL;
	prefix = ft_substr(value, 0, start);
	if (!prefix)
		return (NULL);
	suffix = ft_substr(value, end + 1, ft_strlen(value));
	if (!suffix)
		return (free_2_str(prefix, suffix));
	if (str == NULL)
		ret = ft_strjoin(prefix, suffix);
	else
	{
		tmp = ft_strjoin(prefix, str);
		if (!tmp)
			return (free_2_str(prefix, suffix));
		ret = ft_strjoin(tmp, suffix);
	}
	free_replace_string(prefix, suffix, value, tmp);
	return (ret);
}
