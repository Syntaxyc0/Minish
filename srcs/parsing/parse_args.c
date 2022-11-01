/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:07:07 by jbesnier          #+#    #+#             */
/*   Updated: 2022/11/01 14:07:09 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_args_size(t_token *token)
{
	t_token	*tmp;
	int		ret;

	ret = 0;
	tmp = token;
	while (tmp != NULL && tmp->type == WORD)
	{
		ret += 1;
		tmp = tmp->next;
	}
	return (ret);
}

int	parse_word(t_token *token, char **args, int i)
{
	args[i] = ft_strdup(token->value);
	if (!args[i])
	{	
		write_error_message(ERR_MALLOC);
		free_array(args);
		return (1);
	}
	return (0);
}

int	parse_args(t_mini *mini, t_token *token, t_command *command)
{
	char	**args;
	int		i;
	t_token	*tmp;

	i = 0;
	args = malloc(sizeof(char *) * (get_args_size(token) + 1));
	if (!args)
	{
		write_error_message(ERR_MALLOC);
		return (EXIT_FAILURE);
	}
	while (token != NULL && token->type == WORD)
	{
		if (parse_word(token, args, i))
			return (1);
		tmp = token->next;
		delete_token(mini, token);
		token = tmp;
		i++;
	}
	args[i] = NULL;
	command->args = args;
	return (0);
}
