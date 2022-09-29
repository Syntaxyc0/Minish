/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregoiregobert <gregoiregobert@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:51:18 by gregoiregob       #+#    #+#             */
/*   Updated: 2022/09/21 14:51:18 by gregoiregob      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define ERR_MALLOC "msh : Failed to allocate memory.\n"
# define ERR_SYNTAX "msh : syntax error near unexpected token.\n"
# define ERR_INPUT "msh : Invalid input.\n"
# define ERR_QUOTES "msh : Unclosed quotes\n"
# define ERR_ARG "msh : too many arguments"

extern int	g_exit_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_sort
{
	char			*key;
	char			*value;
	struct s_sort	*next;
	struct s_sort	*previous;
}	t_sort;

typedef struct s_export
{
	char			*key;
	struct s_export	*next;
}	t_export;

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_mini
{
	t_env		*myenv;
	t_export	*myexport;
	t_token		*tokens;
}	t_mini;

//error

int		write_error_message(char *message);
void	free_mini(t_mini *mini);
void	free_mini_exit_msg(t_mini *mini, char *message);
void	free_letters(t_mini *mini);
void	free_tokens(t_mini *mini);
void	free_env(t_mini *mini);
void	Sfree_export(t_mini *mini);

//builtins

void	cd(t_mini *mini, int ac, char **av);
void	env(t_mini *mini);
void	export(t_mini *mini, int ac, char **av);
char	*get_path(char **av);
char	*get_pwd();
void	import(t_mini *mini, int ac, char **av);
void	import_env(t_mini *mini, char *s);
void	import_export(t_mini *mini, char *s);
void	init_myenv(t_mini *mini, char *key, char *value);
void	init_myexport(t_mini *mini, char *s);
void	lst_del_unset_env(t_env *tmp, t_env *previous);
void	lst_del_unset_export(t_export *tmp, t_export *previous);
void	old_pwd(t_mini *mini);
void	pwd(void);
void	unset(t_mini *mini, int ac, char **av);
void	unset_in_env(t_mini *mini, char **av);
void	unset_in_export(t_mini *mini, char **av);
char	*home_env(t_mini *mini);
int		is_builtin(char *arg);
int		is_egal(char *s);
int		is_space_before_egal(char *s);
int		str_big(char *a, char *b);

//parsing

t_mini	*init_mini(void);
int		len_quote(char *str, int i);
int		check_quote_syntax(char	*str);
int		len_quote(char *str, int i);
void	check_tokens(t_mini *mini);
void	expander(t_mini *mini);
void	parse_token(t_mini *mini, char *str);
int		contains_exp_sign(char *str);
void	expand_env(t_mini *mini, t_token *token, int i);

//env

void	add_envelem(t_mini *mini, char *key, char *value);
char	*get_env_value(t_mini *mini, char *key);
int		get_env(char **env, t_mini *mini);

#endif