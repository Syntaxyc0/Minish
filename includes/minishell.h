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

# define ERR_MALLOC "Failed to allocate memory."
# define ERR_SYNTAX "Invalid syntax."

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_sort
{
	char			*key;
	char			*value;
	struct s_sort	*next;
	struct s_sort	*previous;
}	t_sort;

typedef struct	s_export
{
	char			*key;
	struct s_export	*next;
}	t_export;

typedef struct	s_letters
{
	int type;
	char    value;
	struct s_letters    *next;
}	t_letters;

typedef struct	s_token
{
	int type;
	char    *value;
	struct  s_token *next;
}	t_token;

typedef struct	s_mini
{
	t_env		*myenv;
	t_export	*myexport;
	t_letters	*letters;
	t_token		*tokens;
	t_sort		*sort;
}	t_mini;

enum	letter_type
{
	WORD = 1,
	IN = 2,
	OUT = 3,
	DOLL = 4,
	PIPE = 5,
	SQUOTE = 6,
	DQUOTE = 7
};

enum	token_type
{
	HEREDOC = 8,
	APPEND = 9,
	COMMAND = 10,
	SQUOTED = 11
};

//error

int		write_error_message(char *message);
void    free_mini(t_mini *mini);
void	free_mini_exit_msg(t_mini *mini, char *message);
void    free_letters(t_mini *mini);
void	free_tokens(t_mini *mini);
void    free_env(t_mini *mini);
void    free_export(t_mini *mini);

//builtins

int	is_builtin(char *arg);

//parsing

t_mini	*init_mini(void);
int		check_quote_syntax(char	*str);
int		len_quote(char *str, int i);

//env

void    add_envelem(t_mini *mini, char *key, char *value);
void	export(t_mini *mini, int ac, char **av);
void	import(t_mini *mini, int ac, char **av);
void	import_env(t_mini *mini, char *s);
void	import_export(t_mini *mini, char *s);
void    init_myenv(t_mini *mini, char *key, char *value);
void	init_myexport(t_mini *mini, char *s);
void	lst_del_unset(t_env *tmp, t_env *previous);
void	sort_env_export(t_mini *mini);
void	unset(t_mini *mini, int ac, char **av);
char	*get_env_value(t_mini *mini, char *key);
int		get_env(char **env, t_mini *mini);
int		is_egal(char *s);
int		str_big(char *a, char *b);

#endif