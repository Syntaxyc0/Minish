#include "minishell.h"

char    *get_env_value(t_mini *mini, char *key)
{
    t_env *tmp;

    tmp = mini->myenv;
    while (tmp != NULL)
    {
        if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}