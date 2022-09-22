#include "minishell.h"

int	len_quote(char *str, int i)
{
	char quote;
	int	len;

	quote = str[i];
	len = 0;
	while (str[i + len] && str[i + len] != quote)
		len++;
	return (len);
}

int	check_quote_syntax(char	*str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (str[i] == '\0') // guillemets non fermées
			return (0);
		i++;
	}
	return (1);
}