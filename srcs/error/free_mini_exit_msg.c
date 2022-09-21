#include "minishell.h"

void    free_letters(t_mini *mini)
{
    t_letters   *tmp;
    t_letters   *save;

    tmp = mini->letters;
    while (tmp != NULL)
    {
        save = tmp;
        tmp = tmp->next;
        free(save);
    }
}

void	free_tokens(t_mini *mini)
{
	t_token	*tmp;
	t_token	*tofree;
	
	tmp = mini->tokens;
	while (tmp != NULL)
	{
		tofree = tmp;
		tmp = tmp->next;
		free(tofree->value);
		free(tofree);
	}
}

void    free_env(t_mini *mini)
{
    t_env *tmp;
    t_env   *tofree;

    tmp = mini->myenv;
    while (tmp != NULL)
    {
		if (tmp->key)
        	free(tmp->key);
        if (tmp->value)
			free(tmp->value);
        tofree = tmp;
        tmp = tmp->next;
        free(tofree);
    }
}

void    free_mini(t_mini *mini)
{
	if (mini->myenv)
		free_env(mini);
	if (mini->letters)
		free_letters(mini);
	if (mini->tokens)
		free_tokens(mini);
	free(mini);
}

void	free_mini_exit_msg(t_mini *mini, char *message)
{
	write_error_message(message);
	free_mini(mini);
	exit(1);
}