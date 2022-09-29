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
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>


# define ERR_MALLOC "msh : Failed to allocate memory.\n"
# define ERR_SYNTAX "msh : syntax error near unexpected token.\n"
# define ERR_INPUT "msh : Invalid input.\n"
# define ERR_QUOTES "msh : Unclosed quotes\n"

extern int	g_exit_status;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_export
{
	char			*value;
	struct s_export	*next;
}	t_myexport;


typedef struct	s_token
{
	char    *value;
	int		type;
	int		needs_expansion;
	struct  s_token *next;
}	t_token;

typedef struct	s_mini
{
	t_env		*myenv;
	t_myexport	*myexport;
	t_token		*tokens;
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
void    free_mini(t_mini *mini);
void	free_mini_exit_msg(t_mini *mini, char *message);

//builtins

int	is_builtin(char *arg);

//parsing

t_mini	*init_mini(void);
int	len_quote(char *str, int i);
int	check_quote_syntax(char	*str);
int	len_quote(char *str, int i);
void	check_tokens(t_mini *mini);
t_token	*create_token(char *value);
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

//env

void    add_envelem(t_mini *mini, char *key, char *value);
void	export(t_mini *mini, int ac, char **av);
void	import(t_mini *mini, int ac, char **av);
void	import_env(t_mini *mini, char *s);
void	import_export(t_mini *mini, char *s);
void    init_myenv(t_mini *mini, char *key, char *value);
void	lst_del_unset(t_env *tmp, t_env *previous);
void	sort_env_export(t_mini *mini);
void	unset(t_mini *mini, int ac, char **av);
char	*get_env_value(t_mini *mini, char *key);
int		get_env(char **env, t_mini *mini);
int		is_egal(char *s);
int		str_big(char *a, char *b);

#endif