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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

# define ERR_MALLOC "msh : Failed to allocate memory."
# define ERR_SYNTAX "msh : syntax error near unexpected token "
# define ERR_QUOTES "msh : Unclosed quotes"
# define ERR_ARG "wrong number of arguments\n"
# define ERR_NOFILE "msh : no such file or directory"
# define ERR_NORIGHT "msh : permission denied"
# define ERR_INVALID " : Invalid input."
# define ERR_AMBI ": ambiguous redirect"
# define ERR_VALIDARG "msh : not a valid identifier\n"

# define MINI "Minishell: "

/*
DEFINE io :
first = -2
+ in = 2
+ out = -1
+ in/out = 3

mid = 2
+ in = 2
+ out = 3
+ in/out = 3

last = 1
+ in = 1
+ out = 3
+ in/out = 3

alone = 0
+ in = 1
+ out = -1
+ in/out = 3

builtin + out = 4

dont exec = -3
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
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*filename;
	char			*heredoc_name;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
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
	char		*line;
	char		**all_path;
	char		**environment;
	struct sigaction	sig_quit;
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

//signals

void	ft_signal(int signal);
void	ft_sigint_handle(t_mini *mini);
void	process_sig_handle(void);
void	ft_handle_exit(t_mini *mini);
void	heredoc_sig_handle(void);
void	heredoc_d(int signal);
void	heredoc_c(int signal);
void	child_sig_handler(t_mini *mini);
void	sigint_process(int signal);
void	sigquit_process(int signal);
void	signals_process(void);

//error

void	free_array(char **array);
void	free_commands(t_mini *mini);
void	free_env(t_mini *mini);
void	free_export(t_mini *mini);
void	free_letters(t_mini *mini);
void	free_mini(t_mini *mini);
void	free_mini_exit_msg(t_mini *mini, char *message);
void	free_tokens(t_mini *mini);
void	free_line_null(t_mini *mini);
void	exit_free_status(t_mini *mini, int ges);
void	exit_free_status_msg(t_mini *mini, int ges, char *msg);
void	exit_perror(int ges);
void	perror_ges(int ges);
int		error_args(char *msg, char *token, int errcode);
int		error_redisplay_line(char *msg, char *token, int errcode);
int		error_mini(t_mini *mini);
int		return_perror(int ges, int ret);
int		write_error_message(char *message);

//builtins

void	cd(t_command *cmd, t_mini *mini);
int		chdir_res(char *curpath, t_mini *mini);
void	echo(t_command *cmd, t_mini *mini);
void	echo_nl(t_command *cmd, t_mini *mini);
void	echo_print_args(t_command *cmd, t_mini *mini, int i);
void	env(t_mini *mini, t_command *cmd);
void	exit_one_args(t_command *cmd, t_mini *mini);
void	exit_no_arg(t_mini *mini);
void	export(t_mini *mini, t_command *cmd);
void	ft_exit(t_command *cmd, t_mini *mini);
void	import(t_mini *mini, int ac, char **av);
void	import_env(t_mini *mini, char *s);
void	import_export(t_mini *mini, char *s);
void	init_myenv(t_mini *mini, char *key, char *value);
void	init_myexport(t_mini *mini, char *s);
void	lst_del_unset_env(t_env *tmp, t_env *previous);
void	lst_del_unset_export(t_export *tmp, t_export *previous);
void	old_pwd(t_mini *mini);
void	push_in_env(t_mini *mini, char *curpath);
void	pwd(t_command *cmd, t_mini *mini);
void	unset(t_mini *mini, t_command *cmd);
void	unset_in_env(t_mini *mini, char *av);
void	unset_in_export(t_mini *mini, char *av);
char	*back_repo(char *curpath, int dot_count, t_mini *mini);
char	*get_path(char **av, t_mini *mini);
char	*get_pwd(t_mini *mini);
char	*home_env(t_mini *mini);
char	*pwd_get_cwd(t_mini *mini, int i, char *ret);
char	*two_dot(char *curpath, t_mini *mini);
int		already_in_env(t_mini *mini, char *key, char *value);
int		already_in_export(t_mini *mini, char *key);
int		check_arg(char *args);
int		echo_n_manager(t_command *cmd);
int		is_builtin(char *arg);
int		is_egal(char *s);
int		is_space_before_egal(char *s);
int		str_isdigit(char *str);

//parsing

t_mini	*init_mini(void);
int		len_quote(char *str, int i);
int		check_quote_syntax(char	*str);
int		check_invalid_char(char *input);
int		len_quote(char *str, int i);
int		handle_append(t_mini *mini, t_token *token);
int		handle_heredoc(t_mini *mini, t_token *token);
int		check_tokens(t_mini *mini);
t_token	*create_token(char *value);
void	delete_token(t_mini *mini, t_token *token);
int		parse_token(t_mini *mini, char *str);
void	get_token_type(t_mini *mini);
int		check_syntax(t_mini *mini);
int		check_expandredirs(t_mini *mini);
void	get_redir_types(t_mini *mini);
char	*replace_string(char *value, char *str, int start, int end);
int		contains_exp_sign(char *str);
void	expand_env(t_mini *mini, t_token *token, int i);
int		contains_exp_sign(char *str);
char	*handle_exp_quote(t_mini *mini, char *str, int *free1);
int		expand(t_mini *mini, t_token *token, int i);
int		expander(t_mini *mini);
char	*split_token(t_mini *mini, t_token *token);
void	parse_spaces(t_mini *mini);
int		remove_quotes(t_mini *mini);
int		remove_markers(t_mini *mini);
int		parse_redir(t_mini	*mini, t_token *token, t_command *command);
int		parse_args(t_mini *mini, t_token *token, t_command *command);
int		parse_exec_form(t_mini	*mini);
int		parser(t_mini *mini, char *line);

//env

void	add_envelem(t_mini *mini, char *key, char *value);
char	*get_env_value(t_mini *mini, char *key);
int		is_egal(char *s);
int		get_env(char **env, t_mini *mini);

//exec

void	builtin_process(t_command *cmd, t_mini *mini);
void	execution(t_command *cmd, t_mini *mini);
void	ft_append(t_command *cmd, t_redir *redir);
void	heredoc_fork(t_mini *mini, t_redir *redir, int fd);
void	heredoc_annihilator(t_mini *mini);
void	heredoc_child(t_redir *redir, t_mini *mini, int fd);
void	iocondition_heredoc(t_command *cmd);
void	iocondition_redir_in(t_command *cmd);
void	redir_out(t_command *cmd, t_redir *redir);
void	which_builtin(t_command *cmd, t_mini *mini);
void	which_builtin2(t_command *cmd, t_mini *mini);
char	*already_exist(t_redir *redir, t_command *cmd, t_mini *mini);
char	*heredoc_tmp_add(t_mini *mini, char *str);
int		access_in(t_command *cmd2);
int		check_relative(t_mini *mini, t_command *cmd);
int		dup_io(t_command *cmd);
int		exec(t_mini *mini);
int		ft_access(t_command *cmd, t_mini *mini);
int		ft_close_all(t_mini *mini);
int		ft_heredoc(t_command *cmd, t_redir *redir, t_mini *mini);
int		ft_open_all(t_mini *mini);
int		init_pipe(t_mini *mini);
int		processes(t_mini *mini);
int		redir_in(t_command *cmd, t_redir *redir);

//utils

void	get_all_path(t_mini *mini);
char	*ft_strjoin_free(char *s1, char *s2, int free1, int free2);
int		any_redir_out(t_command *cmd);
int		cmd_args_len(t_command *cmd);
int		cmd_len(t_mini *mini);
int		str_big(char *a, char *b);

#endif
