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

SRCS = 	ft_signal.c \
		ft_signal_handle.c \
		write_error_message.c \
		free_mini_exit_msg.c \
		error_redisplay_line.c \
		init_mini.c \
		check_quote.c \
		parse_tokens.c \
		check_tokens.c \
		get_token_type.c \
		check_syntax.c \
		parser.c \
		get_redir_types.c \
		expander.c \
		parse_cmds.c \
		parse_spaces.c \
		remove_empty_tokens.c \
		remove_quotes.c \
		is_builtin.c \
		get_env.c \
		get_env_value.c \
		unset.c \
		export.c \
		env.c	\
		main.c \
		cd.c	\
		cd2.c	\
		pwd.c	\
		echo.c	\
		utils.c \
		exec.c	\
		fork_execution.c \
		open_redir.c  \
		builtin_process.c	\
		exit.c	\
		
CC = gcc $(FSANITIZE)

CFLAGS = -MMD -Wall -Werror -Wextra

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
		make clean -C $(FT_PATH)
		${RM} $(OBJ_PATH)

fclean:
		make fclean -C $(FT_PATH)
		make clean
		${RM} ${NAME}

re:
	make fclean
	make all

-include $(DEPS)

.PHONY:			all clean fclean re
