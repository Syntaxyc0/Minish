#include "minishell.h"

t_token	*create_token(t_mini *mini, char *value, int type)
{
	t_token	*ret;

	ret = malloc(sizeof(t_token));
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	ret->value = value;
	ret->type = type;
	ret->next = NULL;
	return (ret);
}

void	addback_token(t_mini *mini, t_token *token)
{
	t_token	*tmp;

	tmp = mini->tokens;
	if (tmp == NULL)
	{
		mini->tokens = token;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = token;
}

int get_type(char c)
{
    if (c == '<')
        return (IN);
    else if (c == '>')
        return (OUT);
    else if (c == '$')
        return (DOLL);
    else if (c == '|')
        return (PIPE);
    else if (c == '\'')
        return (SQUOTE);
    else if (c == '\"')
        return (DQUOTE);
    else
        return (WORD);
}

void	parse_squote(t_mini *mini, char *str, int *i)
{
	t_token	*token;
	char	*value;
	int	j;

	j = len_quote(str, i);
	value = ft_substr(str, i + 1, j);
	if (!value)
		free_mini_exit_msg(mini, ERR_MALLOC);
	token = create_token(mini, value, SQUOTED);
	addback_token(mini, token);
	*i += j + 1;
}

void	parse_token(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	if (get_type(str[i]) == SQUOTE)
		parse_squote(mini, str, i);

}

void	parse_line_into_tokens(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	if (!check_quote_syntax(str))
		free_mini_exit_msg(mini, ERR_SYNTAX);
}