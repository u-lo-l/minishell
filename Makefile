# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 19:20:57 by dkim2             #+#    #+#              #
#    Updated: 2022/05/19 18:33:17 by dkim2            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES : .c .o

CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = minishell

# 사용하는 파일들 여기에 추가
OBJS_FILES = read_command.o\
				main.o\
				signal_handler.o
OBJS = ${addprefix SRC/, ${OBJS_FILES}}

SRCS = ${OBJS.o=.c}

# 사용하는 헤더들 여기에 추가
HEADER_FILES= minishell.h \
			  minishell_datastructrue.h
HEADERS = ${addprefix INC/, ${HEADER_FILES}}

all : ${NAME}

clean : 
		${RM} ${OBJS}

fclean : clean
		${RM} ${NAME}

re : clean all

.PHONY : all clean fclean re

# 컴파일 옵션 다 써놔서 에러 뜰 덴데 걍 하면 됨
${NAME} : ${OBJS}
		${CC} -o ${NAME} ${OBJS} -lreadline \
		-L/Users/dkim2/.brew/Cellar/readline/8.1.2/lib \
		-I/Users/dkim2/.brew/Cellar/readline/8.1.2/include \
		-L/Users/yyoo/.brew/Cellar/readline/8.1.2/lib \
		-I/Users/yyoo/.brew/Cellar/readline/8.1.2/include

.c.o : ${HEADERS}
		${CC} ${CFLAGS} -c $< -o $@ \
		-I/Users/dkim2/.brew/Cellar/readline/8.1.2/include \
		-I/Users/yyoo/.brew/Cellar/readline/8.1.2/include
