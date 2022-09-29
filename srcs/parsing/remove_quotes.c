#include "minishell.h"

int	contains_quote(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		if (str[i] == "\"")
			return (2);
		i++;
	}
	return (0);
}

get_next_quote_index(char	*str, int start, char quote)
{

}

int	remove_quotes(t_mini *mini)
{
	t_token	*token;
	int		start;
	int		end;

	start = 0;
	end = 0;
	token = mini->tokens;
	while (token != NULL)
	{
		if (token->type == WORD)
		{
			if (contains_quote(token->value))
			{

			}
		}
		token = token->next;
	}
}