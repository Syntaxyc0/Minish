NAME = minishell

FSANITIZE = -g3 -fsanitize=address

SRCSPATH = srcs

FT_PATH = libft

ERR_PATH = error

BUILT_PATH = builtins

ENV_PATH = env

PARSE_PATH = parsing

SIGNAL_PATH = signals

EXEC_PATH = exec

OBJ_PATH = obj

UTILS_PATH = utils

HEADERS = includes \

SRCS = 	ft_signal.c				\
		ft_signal_handle.c		\
		write_error_message.c	\
		free_utils.c 			\
		free_utils2.c 			\
		free_mini_exit_msg.c	\
		error_redisplay_line.c	\
		init_mini.c				\
		check_quote.c			\
		parse_tokens.c			\
		check_tokens.c			\
		get_token_type.c		\
		check_syntax.c			\
		parser.c 				\
		check_ambiguous.c 		\
		check_invalid_char.c	\
		get_redir_types.c 		\
		check_handle_redir.c	\
		replace_string.c 		\
		handle_exp_quote.c		\
		expand.c				\
		expander.c 				\
		parse_redir.c			\
		parse_args.c			\
		parse_cmds.c 			\
		split_token.c			\
		parse_spaces.c 			\
		remove_quotes.c 		\
		remove_markers.c		\
		is_builtin.c 			\
		get_env.c 				\
		get_env_value.c 		\
		unset.c 				\
		export.c 				\
		export2.c				\
		env.c					\
		main.c 					\
		cd.c					\
		cd2.c					\
		pwd.c					\
		echo.c					\
		utils.c 				\
		ft_strjoin_free.c		\
		exec.c					\
		fork_execution.c 		\
		open_redir.c  			\
		open_redir2.c			\
		open_redir3.c			\
		builtin_process.c		\
		exit.c					\
		io_condition.c			\
		
CC = gcc #$(FSANITIZE)

CFLAGS = -MMD -Wall -Werror -Wextra -g3

RM = rm -rf

OBJS =  $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))

DEPS = $(OBJS:.o=.d)

SUPPR		=	\033[00m
GRAS		=	\033[01m
CLIGNO		=	\033[05m
GREEN		=	\033[32m
YELLOW		=	\033[33m
RED			=	\033[31m
WHITE		=	\033[37m

vpath %.h $(HEADERS)
vpath %.c $(SRCSPATH)			\
 	$(SRCSPATH)/$(ERR_PATH) 	\
	$(SRCSPATH)/$(BUILT_PATH) 	\
	$(SRCSPATH)/$(ENV_PATH) 	\
	$(SRCSPATH)/$(PARSE_PATH) 	\
	$(SRCSPATH)/$(EXEC_PATH) 	\
	$(SRCSPATH)/$(SIGNAL_PATH) 	\
	$(SRCSPATH)/$(UTILS_PATH) 	\


vpath %.o $(OBJ_PATH)

all: $(NAME)

$(NAME):		$(OBJS)
			@make -C $(FT_PATH)
			@$(CC) $(CFLAGS) $(OBJS) -I $(HEADERS) -I libft/include -L$(FT_PATH) -lft -lreadline -o $(NAME)
			@echo "$(WHITE)Compilation $(GRAS)minishell $(GREEN)$(GRAS)$(CLIGNO)OK$(SUPPR)"

$(OBJ_PATH)/%.o:		%.c
			@$(CC) $(CFLAGS) -I $(HEADERS) -I libft/include -I/usr/include -lreadline -c $< -o $@


$(OBJS):	| $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@make clean -C $(FT_PATH)
	@${RM} $(OBJ_PATH)

fclean:
	@make fclean -C $(FT_PATH)
	@make clean
	@${RM} ${NAME}

re:
	@make fclean
	@make all

-include $(DEPS)

.PHONY:			all clean fclean re
