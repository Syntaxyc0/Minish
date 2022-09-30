NAME = minishell

FSANITIZE = -g3 -fsanitize=address

SRCSPATH = srcs

FT_PATH = libft

ERR_PATH = error

BUILT_PATH = builtins

ENV_PATH = env

PARSE_PATH = parsing

EXEC_PATH = exec

OBJ_PATH = obj

UTILS_PATH = utils

HEADERS = includes \

SRCS = 	write_error_message.c \
		free_mini_exit_msg.c \
		init_mini.c \
		check_quote.c \
		parse_tokens.c \
		check_tokens.c \
		get_token_type.c \
		check_syntax.c \
		get_redir_types.c \
		get_expansion_needs.c \
		expander.c \
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
		pwd.c	\
		echo.c	\
		
CC = gcc $(FSANITIZE)

CFLAGS = -MMD -Wall -Werror -Wextra -lreadline

RM = rm -rf

OBJS =  $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))

DEPS = $(OBJS:.o=.d)

vpath %.h $(HEADERS)
vpath %.c $(SRCSPATH)\
 	$(SRCSPATH)/$(ERR_PATH) \
	$(SRCSPATH)/$(BUILT_PATH) \
	$(SRCSPATH)/$(ENV_PATH) \
	$(SRCSPATH)/$(PARSE_PATH) \
	$(SRCSPATH)/$(EXEC_PATH) \


vpath %.o $(OBJ_PATH)

all: $(NAME)

$(NAME):		$(OBJS)
			make -C $(FT_PATH)
			$(CC) $(CFLAGS) $(OBJS) -I $(HEADERS) -I libft/include -L$(FT_PATH) -lft -o $(NAME)

$(OBJ_PATH)/%.o:		%.c
			$(CC) $(CFLAGS) -I $(HEADERS) -I libft/include -I/usr/include -c $< -o $@


$(OBJS):	| $(OBJ_PATH)

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

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