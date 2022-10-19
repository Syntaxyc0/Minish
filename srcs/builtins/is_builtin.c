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
	if (!ft_strncmp(arg, "echo", str_big(arg, "echo")))
		return (1);
	if (!ft_strncmp(arg, "cd", str_big(arg, "cd")))
		return (1);
	if (!ft_strncmp(arg, "pwd", str_big(arg, "pwd")))
		return (1);
	if (!ft_strncmp(arg, "export", str_big(arg, "export")))
		return (1);
	if (!ft_strncmp(arg, "unset", str_big(arg, "unset")))
		return (1);
	if (!ft_strncmp(arg, "env", str_big(arg, "env")))
		return (1);
	if (!ft_strncmp(arg, "exit", str_big(arg, "exit")))
		return (1);
	return (0);
}
