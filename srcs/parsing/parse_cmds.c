#include "minishell.h"

t_command	*init_cmd(void)
{
	t_command	*ret;

	ret = malloc(sizeof(t_command));
	if (!ret)
		return (NULL);
	ret->fullpath  NULL;
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
		return (NULL);
	ret->type = 0;
	ret->heredoc_expands = 0;
	ret->filename = 0;
	ret->fd[0] = 1;
	ret->fd[1] = 0;
	ret->next = NULL;
}

int	get_heredoc_expand(t_token *token)
{
	char	*str;
	int		i;

	str = token->value;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
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

int	parse_redir(t_mini	*mini, t_token *token, t_command command)
{
	t_redir	*new;

	new = init_redir();
	if (new)
		return (EXIT_FAILURE);
	if (token->type == HEREDOC)
	{
		new->type = HEREDOC;
		new->heredoc_expands = get_heredoc_expand(token->next);
		new->filename = ft_strdup(token->next->value);
		if (!new->filename)
		{
			free(new);
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
			return (EXIT_FAILURE);
		}
	}
	else if (token->type == REDIROUT)
	{
		new->type = REDIROUT;
		new->filename = ft_strdup(token->next->value);
		if (!new->filename)
		{
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
			free(new);
			return (EXIT_FAILURE);
		}
	}
	addback_redir(command, new);
	delete_token(mini, token->next);
	delete_token(mini, token);
	return (EXIT_SUCCESS);
}

int	parse_cmd(t_mini *mini)
{
	t_command	*new;
	t_token		*token;

	new = init_cmd();
	if (!new)
		return (EXIT_FAILURE);
	while (token->next != NULL && token->type != PIPE)
	{
		token = mini->tokens;
		if (token->type == REDIRIN || token->type == REDIROUT || token->type == HEREDOC || token->type == APPEND)
		{
			if (!parse_redir(mini, token, new))
			{
				free(new);
				return (EXIT_FAILURE);
			}
		}
		else // TODO: gerer les mots et pipe
			token = token->next;
	}
}

int	parse_exec_form(t_mini	*mini)
{
	t_token		*token;
	t_command	*cmd;

	token = mini->tokens;
	while (token != NULL)
	{
		if (!parse_cmd(mini, token))
			return (EXIT_FAILURE);
	}
}