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
		printf("key : %s\nvalue : %s\n", test->key, test->value);
		test = test->next;
	}
	printf("__________________________________\n");
	export(mini, argc, argv);
	test = mini->myenv;
	while (test != NULL)
	{
		printf("key : %s\nvalue : %s\n", test->key, test->value);
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
int	g_exit_status;

int main(int argc, char **argv, char **env)
{
	t_mini *mini;
	t_token	*token;
	char	*line;

	g_exit_status = 0;
	mini = init_mini();
	(void)argc;
	(void)argv;
	line = readline("Minishell: ");
	parse_token(mini, line);
	check_tokens(mini);
	get_env(env, mini);
	expander(mini);
	parse_spaces(mini);
	token = mini->tokens;
	while (token)
	{
		printf("token value : %s\ntoken type : %d\n\n", token->value, token->type);
		token = token->next;
	}
	free(line);
	free_mini(mini);
}
