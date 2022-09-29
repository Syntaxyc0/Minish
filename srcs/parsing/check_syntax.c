#include "minishell.h"

int	check_syntax(t_mini *mini)
{
	t_token	*token;

	token = mini->tokens;
	while (token != NULL)
	{
		if (token->type == REDIR)
		{
			if (token->next == NULL)
				return (0);
			if (token->next->type == REDIR)
				return (0);
			if (token->next->type == PIPE)
				return (0);
		}
		if (token->type == PIPE)
		{
			if (token->next == NULL)
				return (0);
			if (token->next->type == PIPE)
				return (0);
		}
		token = token->next;
	}
	return (1);
}