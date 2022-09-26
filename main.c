#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_mini *mini;
	int		env_set;
	t_env *test;

	mini = init_mini();
	env_set = get_env(env, mini);
	(void)env_set;
	(void)argc;
	(void)argv;
	test = mini->myenv;
	while (test != NULL)
	{
		printf("key : %s\nvalue : %s\n\n", test->key, test->value);
		test = test->next;
	}
	free_mini(mini);
}