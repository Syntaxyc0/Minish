#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>

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
    int type;
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
    QUOTE = 6,
    DQUOTE = 7,
	QM = 8
};

enum token_type
{
    HEREDOC = 8,
    APPEND = 9,
    COMMAND = 10,
	DOLLQM = 11
};

//error

int	write_error_message(char *message);

//builtins

int	is_builtin(char *arg);

#endif