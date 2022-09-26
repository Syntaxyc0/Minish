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

# define ERR_MALLOC "msh : Failed to allocate memory.\n"
# define ERR_SYNTAX "msh : syntax error near unexpected token.\n"
# define ERR_INPUT "msh : Invalid input.\n"

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}   t_env;

typedef struct s_letters
{
    int type;
    char    value;
    struct s_letters    *next;
}   t_letters;

typedef struct s_token
{
    char    *value;
    struct  s_token *next;
}   t_token;

typedef struct s_mini
{
    t_env   *myenv;
    t_letters   *letters;
	t_token		*tokens;
}   t_mini;

enum letter_type
{
    WORD = 1,
    IN = 2,
    OUT = 3,
    DOLL = 4,
    PIPE = 5,
    SQUOTE = 6,
    DQUOTE = 7
};

enum token_type
{
    HEREDOC = 8,
    APPEND = 9,
    COMMAND = 10,
	SQUOTED = 11,
    DQUOTED = 12
};

//error

void    free_mini(t_mini *mini);
int	write_error_message(char *message);
void	free_mini_exit_msg(t_mini *mini, char *message);

//builtins

int	is_builtin(char *arg);

//parsing

t_mini	*init_mini(void);
int	len_quote(char *str, int i);
int	check_quote_syntax(char	*str);
int	len_quote(char *str, int i);
void	check_tokens(t_mini *mini);
void	expander(t_mini *mini);
void	parse_token(t_mini *mini, char *str);

//env

char    *get_env_value(t_mini *mini, char *key);
int   get_env(char **env, t_mini *mini);

#endif