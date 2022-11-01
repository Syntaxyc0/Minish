/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:28:24 by jbesnier          #+#    #+#             */
/*   Updated: 2022/11/01 11:33:25 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*init_redir(void)
{
	t_redir	*ret;

	ret = malloc(sizeof(t_redir));
	if (!ret)
	{
		write_error_message(ERR_MALLOC);
		return (NULL);
	}
	ret->type = 0;
	ret->filename = NULL;
	ret->heredoc_name = NULL;
	ret->next = NULL;
	return (ret);
}

void	addback_redir(t_command *cmd, t_redir *redir)
{
	t_redir	*tmp;

	tmp = cmd->redir;
	if (tmp == NULL)
	{
		cmd->redir = redir;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = redir;
}

int	create_redir_type(t_redir *new, t_token *token, int type)
{
	new->type = type;
	new->filename = ft_strdup(token->next->value);
	if (!new->filename)
	{
		free(new);
		write_error_message(ERR_MALLOC);
		return (1);
	}
	return (0);
}

int	parse_type_redir(t_redir *new, t_token *token)
{
	if (token->type == HEREDOC)
	{
		if (create_redir_type(new, token, HEREDOC))
			return (1);
	}
	else if (token->type == REDIRIN)
	{
		if (create_redir_type(new, token, REDIRIN))
			return (1);
	}
	else if (token->type == REDIROUT)
	{
		if (create_redir_type(new, token, REDIROUT))
			return (1);
	}
	else if (token->type == APPEND)
	{
		if (create_redir_type(new, token, APPEND))
			return (1);
	}
	return (0);
}

int	parse_redir(t_mini	*mini, t_token *token, t_command *command)
{
	t_redir	*new;

	new = init_redir();
	if (!new)
		return (EXIT_FAILURE);
	if (parse_type_redir(new, token))
		return (1);
	addback_redir(command, new);
	delete_token(mini, token->next);
	delete_token(mini, token);
	return (0);
}
