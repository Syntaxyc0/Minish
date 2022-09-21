# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggobert <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 15:28:31 by ggobert           #+#    #+#              #
#    Updated: 2021/12/09 10:55:52 by ggobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_atoi.c \
			ft_isdigit.c \
			ft_memset.c \
			ft_strlcpy.c \
			ft_substr.c \
			ft_bzero.c \
			ft_isprint.c \
			ft_split.c \
			ft_strlen.c \
			ft_tolower.c \
			ft_calloc.c \
			ft_memchr.c \
			ft_strchr.c \
			ft_strncmp.c \
			ft_toupper.c \
			ft_isalnum.c \
			ft_memcmp.c \
			ft_strdup.c \
			ft_strnstr.c \
			ft_isalpha.c \
			ft_memcpy.c \
			ft_strjoin.c \
			ft_strrchr.c \
			ft_isascii.c \
			ft_strlcat.c \
			ft_strtrim.c \
			ft_memmove.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_striteri.c \
			get_next_line.c \
			get_next_line_utils.c 
SRCS2	=	ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c 
OBJS	=	${SRCS:.c=.o}
OBJSB	=	${SRCS2:.c=.o}
NAME	=	libft.a
CC		=	gcc
RM		=	rm -f
CFLAGS	=	-Wall -Wextra -Werror
SUPPR	=	\033[00m
GRAS	=	\033[01m
CLIGNO	=	\033[05m
RED		=	\033[31m
GREEN	=	\033[32m
WHITE	=	\033[37m
INVERSE	=	\033[07m

.c.o	:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}	:	${OBJS}
	@ar rcs ${NAME} ${OBJS}
	@echo "$(WHITE)Compilation $(GRAS)LIBFT $(GREEN)$(GRAS)$(CLIGNO)OK$(SUPPR)"

all		:	${NAME}

clean	: 
	@${RM} ${OBJS} ${OBJSB}

fclean	:	clean
	@${RM} ${NAME}
	@echo "$(WHITE)Libtf is $(GRAS)$(RED)$(CLIGNO)DEAD$(SUPPR)"

re		:	fclean all

bonus	:	${OBJSB}
	ar rcs ${NAME} ${OBJSB}	

.PHONY:		all clean fclean re
