#include "minishell.h"

t_command	*init_cmd(void)
{
	t_command	*ret;

	ret = malloc(sizeof(t_command));
	if (!ret)
	{
		write_error_message(ERR_MALLOC);
		return (NULL);
	}
	ret->fullpath = NULL;
	ret->args = NULL;
	ret->redir = NULL;
	ret->next = NULL;
	return (ret);
}

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

int	parse_redir(t_mini	*mini, t_token *token, t_command *command)
{
	t_redir	*new;

	new = init_redir();
	if (!new)
		return (EXIT_FAILURE);
	if (token->type == HEREDOC)
	{
		new->type = HEREDOC;
		new->filename = ft_strdup(token->next->value);
		if (!new->filename)
		{
			free(new);
			write_error_message(ERR_MALLOC);
			return (EXIT_FAILURE);
		}
	}
	else if (token->type == REDIRIN)
	{
		new->type = REDIRIN;
		new->filename = ft_strdup(token->next->value);
		if (!new->filename)
		{
			free(new);
			write_error_message(ERR_MALLOC);
			return (EXIT_FAILURE);
		}
	}
	else if (token->type == REDIROUT)
	{
		new->type = REDIROUT;
		new->filename = ft_strdup(token->next->value);
		if (!new->filename)
		{
			write_error_message(ERR_MALLOC);
			free(new);
			return (EXIT_FAILURE);
		}
	}
	else if (token->type == APPEND)
	{
		new->type = APPEND;
		new->filename = ft_strdup(token->next->value);
		if (!new->filename)
		{
			write_error_message(ERR_MALLOC);
			free(new);
			return (EXIT_FAILURE);
		}
	}
	addback_redir(command, new);
	delete_token(mini, token->next);
	delete_token(mini, token);
	return (EXIT_SUCCESS);
}

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
		args[i] = ft_strdup(token->value);
		if (!args[i])
		{	
			write_error_message(ERR_MALLOC);
			free_array(args);
			return (1);
		}
		tmp = token->next;
		delete_token(mini, token);
		token = tmp;
		i++;
	}
	args[i] = NULL;
	command->args = args;
	return (0);
}

void	add_command(t_mini *mini, t_command *cmd)
{
	t_command *tmp;

	tmp = mini->commands;
	if (tmp == NULL)
	{
		mini->commands = cmd;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = cmd;
}

int	parse_cmd(t_mini *mini)
{
	t_command	*new;
	t_token		*token;

	token = mini->tokens;
	if (token != NULL && token->type == PIPE)
		return (0);
	new = init_cmd();
	while (token != NULL && token->type != PIPE)
	{
		if (!new)
			return (EXIT_FAILURE);
		if (token->type == REDIRIN || token->type == REDIROUT || token->type == HEREDOC || token->type == APPEND)
		{
			if (parse_redir(mini, token, new))
			{
				free(new);
				return (EXIT_FAILURE);
			}
			token = mini->tokens;
		}
		else
			token = token->next;
	}
	token = mini->tokens;
	if (parse_args(mini, token, new))
	{
		free(new);
		return (EXIT_FAILURE);
	}
	add_command(mini, new);
	return (0);
}

int	parse_exec_form(t_mini	*mini)
{
	t_token	*tmp;

	tmp = mini->tokens;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (parse_cmd(mini))
			return (EXIT_FAILURE);
		tmp = mini->tokens;
		if (tmp != NULL)
			delete_token(mini, tmp);
		tmp = mini->tokens;
	}
		
	return (0);
}