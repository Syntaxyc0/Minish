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
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>

# define ERR_MALLOC "msh : Failed to allocate memory.\n"
# define ERR_SYNTAX "msh : syntax error near unexpected token.\n"
# define ERR_INPUT "msh : Invalid input.\n"
# define ERR_QUOTES "msh : Unclosed quotes\n"
# define ERR_ARG "msh : too many arguments\n"
# define ERR_NOFILE "msh : no such file or directory\n"
# define ERR_NORIGHT "msh : permission denied\n"
# define ERR_VALIDARG "msh : not a valid identifier\n"

/*
DEFINE io :
io = 0	-> !redir && first && last
io = -1	-> only (redir_out || !last)
io = 1	-> only (redir_in || !first)
io = 2	-> (redir_in || !first) && (redir_out || !last)
*/

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
	char    *value;
	int		type;
	int		needs_expansion;
	struct  s_token *next;
}	t_token;

typedef	struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir *next;
}	t_redir;

typedef	struct s_command
{
	char				*fullpath;
	char				**args;
	int					fd[2];
	int					pid;
	int					io;
	struct s_redir		*redir;
	struct s_command	*next;
}	t_command;

typedef struct s_mini
{
	t_env		*myenv;
	t_export	*myexport;
	t_token		*tokens;
	t_sort		*sort;
	t_command	*commands;
	char		**all_path;
}	t_mini;

enum e_type
{
	WORD = 1,
	PIPE = 2,
	REDIR = 3,
	REDIRIN = 4,
	HEREDOC = 5,
	REDIROUT = 6,
	APPEND = 7
};


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
void	echo(int ac, char **av);
void	env(t_mini *mini);
void	export(t_mini *mini, int ac, char **av);
void	import(t_mini *mini, int ac, char **av);
void	import_env(t_mini *mini, char *s);
void	import_export(t_mini *mini, char *s);
void	init_myenv(t_mini *mini, char *key, char *value);
void	init_myexport(t_mini *mini, char *s);
void	lst_del_unset_env(t_env *tmp, t_env *previous);
void	lst_del_unset_export(t_export *tmp, t_export *previous);
void	old_pwd(t_mini *mini);
void	push_in_env(t_mini *mini, char *curpath);
void	pwd(void);
void	unset(t_mini *mini, int ac, char **av);
void	unset_in_env(t_mini *mini, char **av);
void	unset_in_export(t_mini *mini, char **av);
char	*back_repo(char *curpath, int dot_count);
char	*get_path(char **av);
char	*get_pwd();
char	*home_env(t_mini *mini);
int		check_args(int ac, char **av);
int		is_builtin(char *arg);
int		is_egal(char *s);
int		is_space_before_egal(char *s);

//parsing

t_mini	*init_mini(void);
int		len_quote(char *str, int i);
int		check_quote_syntax(char	*str);
int		len_quote(char *str, int i);
void	check_tokens(t_mini *mini);
t_token	*create_token(char *value);
void	delete_token(t_mini *mini, t_token *token);
void	parse_token(t_mini *mini, char *str);
void	get_token_type(t_mini *mini);
int		check_syntax(t_mini *mini);
void	get_redir_types(t_mini *mini);
char	*replace_string(char *value, char *str, int start, int end);
int		contains_exp_sign(char *str);
void	expand_env(t_mini *mini, t_token *token, int i);
void	get_expansion_needs(t_mini *mini);
void	expander(t_mini *mini);
void	parse_spaces(t_mini *mini);
void	remove_empty_tokens(t_mini *mini);
int		remove_quotes(t_mini *mini);

//env

void	add_envelem(t_mini *mini, char *key, char *value);
char	*get_env_value(t_mini *mini, char *key);
int		get_env(char **env, t_mini *mini);
int		is_egal(char *s);
int		str_big(char *a, char *b);

//utils

void	get_all_path(t_mini *mini);
int		str_big(char *a, char *b);

#endif