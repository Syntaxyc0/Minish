/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:22:31 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/21 14:22:32 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_newline(t_mini *mini)
{
	free_tokens(mini);
	printf("\n");
	return (1);
}

int	parser(t_mini *mini, char *line)
{
	if (parse_token(mini, line))
		return (get_newline(mini));
	parse_spaces(mini);
	if (check_tokens(mini))
		return (get_newline(mini));
	get_redir_types(mini);
	if (check_syntax(mini))
		return (get_newline(mini));
	if (expander(mini))
	{
		free_tokens(mini);
		return (1);
	}
	parse_spaces(mini);
	if (remove_quotes(mini))
		free_mini_exit_msg(mini, ERR_MALLOC);
	if (parse_exec_form(mini))
		free_mini_exit_msg(mini, NULL);
	return (0);
}
