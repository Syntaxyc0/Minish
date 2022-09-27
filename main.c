#include "minishell.h"

/*
int main(int argc, char **argv, char **env)
{
<<<<<<< HEAD
	t_mini		 *mini;
	int			env_set;
	t_env 		*test;
	t_export	*test2;
=======
	t_mini *mini;
	int		env_set;
	t_token *token;
	t_env *test;
>>>>>>> e1f1db1d2fafdfd9a1cd6612117464d3ceedb680

	mini = init_mini();
	
	env_set = get_env(env, mini);
	(void)env_set;
	(void)argc;
	test = mini->myenv;
	test2 = mini->myexport;
	while (test)
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
<<<<<<< HEAD
	printf("__________________________________\n");
	while (test2)
	{
		printf("value : %s\n", test2->value);
		test2 = test2->next;
	}
=======
	
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
>>>>>>> e1f1db1d2fafdfd9a1cd6612117464d3ceedb680
	free_mini(mini);
}
