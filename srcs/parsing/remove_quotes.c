#include "minishell.h"

int	contains_quote(char	*str, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		if (str[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

int	get_next_quote_index(char	*str, int start, char quote)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int	remove_quotes(t_mini *mini)
{
	t_token	*token;
	int		start;
	int		end;

	token = mini->tokens;
	while (token != NULL)
	{
		start = 0;
		end = 0;
		if (token->type == WORD)
		{
			while (contains_quote(token->value, start) == 1)
			{
				start = get_next_quote_index(token->value, start, '\'');
				end = get_next_quote_index(token->value, start + 1, '\'');
				printf("start : %d\nend : %d\n", start, end);
				token->value = replace_string(token->value, NULL, start, start);
				token->value = replace_string(token->value, NULL, end - 1, end - 1);
				printf("token value : %s\n", token->value);
				start = end - 2;
			}
		}
		token = token->next;
	}
	return (EXIT_SUCCESS);
}