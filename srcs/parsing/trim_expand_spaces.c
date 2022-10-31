#include "minishell.h"

char	*trim_spaces_before(char *ret)
{
	int	i;

	i = 0;
	while (ret[i] && ret[i] == ' ')
		i++;
	if (i > 0)
	{
		ret = replace_string(ret, NULL, 0, i - 1);
		if (!ret)
			return (NULL);
	}
	return (ret);
}