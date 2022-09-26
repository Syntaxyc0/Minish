#include "minishell.h"

/*
int main(int argc, char **argv, char **env)
{
	t_mini *mini;
	int		env_set;
	t_token *token;
	t_env *test;

	mini = init_mini();
	
	env_set = get_env(env, mini);
	(void)env_set;
	(void)argc;
	test = mini->myenv;
	while (test != NULL)
	{
		printf("key : %s\nvalue : %s\n\n", test->key, test->value);
		test = test->next;
	}
	
	parse_token(mini, argv[1]);
	token = mini->tokens;
	while (token != NULL)
	{
		printf("token value : %s\ntoken type %d\n\n", token->value, token->type);
		token = token->next;
	}
	free_mini(mini);
}
*/

int main(int argc, char **argv)
{
	t_mini *mini;

	mini = init_mini();
	(void)argc;
	parse_token(mini, argv[1]);
	expander(mini);	
	free_mini(mini);
}
