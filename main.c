#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_mini		 *mini;
	int			env_set;
	t_env 		*test;
	t_export	*test2;

	mini = init_mini();
	env_set = get_env(env, mini);
	(void)env_set;
	(void)argc;
	(void)argv;
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
	printf("__________________________________\n");
	while (test2)
	{
		printf("value : %s\n", test2->value);
		test2 = test2->next;
	}
	free_mini(mini);
}