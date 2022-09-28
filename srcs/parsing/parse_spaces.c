#include "minishell.h"

int	contains_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_only_space(char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

char	*split_token(t_mini *mini, t_token *token)
{
	int	end;
	char	*ret;
	char	*tmp;
	int	start;

	start = 0;
	end = 0;
	while (token->value[start] == ' ' && token->value[start])
		start ++;
	end = start;
	while (token->value[end] != ' ' && token->value[end])
		end++;
	ret = ft_substr(token->value, start, end);
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	if (check_only_space(token->value, end))
	{
		free(token->value);
		token->value = ret;
	}
	tmp = replace_string(token->value, NULL, start, end);
	if (!tmp)
		free_mini_exit_msg(mini, ERR_MALLOC);
	printf("ret : %s\n", ret);
	printf("tmp : %s\n", tmp);
	token->value = ret;
	return (tmp);
}

void	parse_spaces(t_mini *mini)
{
	t_token *token;
	t_token	*new;
	char	*value;
	
	token = mini->tokens;
	while (token != NULL)
	{
		if (contains_space(token->value))
		{
			value = split_token(mini, token);
			if (value == NULL)
				break;
			new = create_token(value);
			new->type = WORD; 
			new->next = token->next;
			token->next = new;
		}
		token = token->next;
	}
	return ;
}