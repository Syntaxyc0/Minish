#include "minishell.h"

void	remove_empty_tokens(t_mini *mini)
{
	t_token	*token;

	token = mini->tokens;
	while (token != NULL)
	{
		if (token->value[0] == '\0')
		{
			delete_token(mini, token);
			token = mini->tokens;
		}
		else
			token = token->next;
	}
}