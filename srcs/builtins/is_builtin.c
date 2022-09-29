/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:48:56 by ggobert           #+#    #+#             */
/*   Updated: 2022/09/29 14:48:56 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strncmp(arg, "echo", ft_strlen(arg)))
		return (1);
	if (!ft_strncmp(arg, "cd", ft_strlen(arg)))
		return (1);
	if (!ft_strncmp(arg, "pwd", ft_strlen(arg)))
		return (1);
	if (!ft_strncmp(arg, "export", ft_strlen(arg)))
		return (1);
	if (!ft_strncmp(arg, "unset", ft_strlen(arg)))
		return (1);
	if (!ft_strncmp(arg, "env", ft_strlen(arg)))
		return (1);
	if (!ft_strncmp(arg, "exit", ft_strlen(arg)))
		return (1);
	return (0);
}
