#include "minishell.h"

void	get_expansion_needs(t_mini *mini)
{
	t_token	*token;

	token = mini->tokens;
	while (token != NULL)
	{
		if (token->type == HEREDOC && token->next->type == WORD)
				token->next->needs_expansion = 0;
		token = token->next;
	}
}