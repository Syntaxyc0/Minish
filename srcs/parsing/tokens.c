#include "minishell.h"

t_token	*create_token(char *value)
{
	t_token	*ret;

	ret = malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->value = value;
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

int	parse_squote(t_mini *mini, char *str, int i)
{
	t_token	*token;
	char	*value;
	int	j;

	j = len_quote(str, i);
	value = ft_substr(str, i + 1, j - 1);
	if (!value)
		free_mini_exit_msg(mini, ERR_MALLOC);
	token = create_token(value);
	if (!token)
	{
		free(value);
		free_mini_exit_msg(mini, ERR_MALLOC);
	}
	addback_token(mini, token);
	return (j + 1);
}

int	parse_dquote(t_mini *mini, char *str, int i)
{
	t_token	*token;
	char	*value;
	int	j;

	j = len_quote(str, i);
	value = ft_substr(str, i + 1, j - 1);
	if (!value)
		free_mini_exit_msg(mini, ERR_MALLOC);
	token = create_token(value);
	if (!token)
	{
		free(value);
		free_mini_exit_msg(mini, ERR_MALLOC);
	}
	addback_token(mini, token);
	return(j + 1);
}

int	parse_pipe(t_mini *mini)
{
	t_token	*token;
	char	*value;

	value = ft_strdup("|");
	if (!value)
		free_mini_exit_msg(mini, ERR_MALLOC);
	token = create_token(value);
	if (!token)
	{
		free(value);
		free_mini_exit_msg(mini, ERR_MALLOC);
	}
	addback_token(mini, token);
	return (1);
}

void	add_token(t_mini *mini, char *str, int *start, int *i)
{
	char	*ret;
	t_token	*token;

	if (*i != *start)
	{
		ret = ft_substr(str, *start, *i - *start);
		if (!ret)
			free_mini_exit_msg(mini, ERR_MALLOC);
		token = create_token(ret);
		addback_token(mini, token);
		*start = *i;
	}
	*i += 1;
	ret = ft_substr(str, *start, *i - *start);
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	token = create_token(ret);
	addback_token(mini, token);
	*start = *i;
}

void	parse_token(t_mini *mini, char *str)
{
	int	i;
	int start;
	t_token	*token;
	char	*ret;

	i = 0;
	start = 0;
	(void)mini;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i += len_quote(str, i) + 1;
		}
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|' || str[i] == ' ')
			add_token(mini, str, &start, &i);
		else
			i++;
	}
	if (i != start)
	{
		ret = ft_substr(str, start, i - start);
		if (!ret)
			free_mini_exit_msg(mini, ERR_MALLOC);
		token = create_token(ret); 
		addback_token(mini, token);
	}
}

void	delete_token(t_mini *mini, t_token *token)
{
	t_token *tmp;

	tmp = mini->tokens;
	if (tmp == token)
	{
		mini->tokens = tmp->next;
		free(token->value);
		free(token);
		return ;
	}
	while (tmp->next != NULL)
	{
		if (tmp->next == token)
		{
			tmp->next = token->next;
			free(token->value);
			free(token);
			return ;
		}
		tmp = tmp->next;
	}
}

int	check_redirin(t_mini *mini, t_token *token)
{
	char	*tmp;

	if (token->next == NULL)
		return (0);
	if (ft_strncmp(token->next->value, ">", 2) == 0)
		return (0);
	if (ft_strncmp(token->next->value, "<", 2) == 0)
	{
		if (token->next->next == NULL)
			return (0);
		if (ft_strncmp(token->next->next->value, "<", 2) == 0)
			return (0);
		if (ft_strncmp(token->next->next->value, ">", 2) == 0)
			return (0);
		tmp = ft_strjoin(token->value, token->next->value);
		if (!tmp)
			free_mini_exit_msg(mini, ERR_MALLOC);
		free(token->value);
		token->value = tmp;
		delete_token(mini, token->next);
		return (1);
	}
	return (1);
}

int	check_redirout(t_mini *mini, t_token *token)
{
	char	*tmp;

	if (token->next == NULL)
		return (0);
	if (ft_strncmp(token->next->value, "<", 2) == 0)
		return (0);
	if (ft_strncmp(token->next->value, ">", 2) == 0)
	{
		if (token->next->next == NULL)
			return (0);
		if (ft_strncmp(token->next->next->value, "<", 2) == 0)
			return (0);
		if (ft_strncmp(token->next->next->value, ">", 2) == 0)
			return (0);
		tmp = ft_strjoin(token->value, token->next->value);
		if (!tmp)
			free_mini_exit_msg(mini, ERR_MALLOC);
		free(token->value);
		token->value = tmp;
		delete_token(mini, token->next);
		return (1);
	}
	return (1);
}

void	check_tokens(t_mini *mini)
{
	t_token	*tokens;

	tokens = mini->tokens;
	while (tokens != NULL)
	{
		if (ft_strncmp(tokens->value, " ", 2) == 0)
		{
			delete_token(mini, tokens);
			tokens = mini->tokens;
		}
		else if (ft_strncmp(tokens->value, "|", 2) == 0)
		{
			if (tokens->next == NULL || ft_strncmp(tokens->next->value, "|", 2) == 0)
				free_mini_exit_msg(mini, ERR_SYNTAX);
		}
		else if (ft_strncmp(tokens->value, "<", 2) == 0)
		{
			if (!check_redirin(mini, tokens))
				free_mini_exit_msg(mini, ERR_SYNTAX);
		}
		else if (ft_strncmp(tokens->value, ">", 2) == 0)
		{
			if (!check_redirout(mini, tokens))
				free_mini_exit_msg(mini, ERR_SYNTAX);
		}
		tokens = tokens->next;
	}
}

int	contains_exp_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += len_quote(str, i);
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

/*void	expand(t_mini *mini, t_token *token, int i)
{
	char	*tmp;

	if (token->value[i + 1] == '\0')
		return ;
	else if (token->value[i + 1] == '?')
		printf("error status :");
	else if (ft_isdigit(token->value[i + 1]))
	{
		while (token->value[i + 1] && ft_isdigit(token->value[i + 1]))
			i++;
		tmp = ft_substr(token->value,i, ft_strlen(token->value) - i);
		free(token->value);
		token->value = tmp;
	}
	else if (ft_isalpha(token->value[i + 1]) || token->value == '_')
	{
		tmp = expand(mini, token->value);
	}
}*/

/*void	expander(t_mini *mini)
{
	t_token	*token;
	int	index;

	token = mini->tokens;
	if (mini->tokens == NULL)
		free_mini_exit_msg(mini, ERR_INPUT);
	while (token != NULL)
	{
		printf("token value : %s\n", token->value);
		index = contains_exp_sign(token->value);
		while (index != -1)
		{
			printf("index %d\n",index);
			if (index)
				expand(mini, token, index);
			index = contains_exp_sign(token->value);
		}
		token = token->next;
	}
}*/
/*
void	parse_line_into_tokens(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	if (!check_quote_syntax(str))
		free_mini_exit_msg(mini, ERR_SYNTAX);
}
*/