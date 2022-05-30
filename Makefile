# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 19:20:57 by dkim2             #+#    #+#              #
#    Updated: 2022/05/30 20:18:42 by yyoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES : .c .o

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

NAME = minishell

LIBS = ./LIBFT/libft.a

# 사용하는 파일들 여기에 추가
OBJS_FILES = main.o\
				read_command.o\
				signal_handler.o\
				env_list.o\
				\
				PARSER/token_node.o\
				PARSER/token_list.o\
				PARSER/token_command.o\
				PARSER/token_tree.o\
				PARSER/tokenize_utils.o\
				PARSER/tokenize_check.o\
				PARSER/tokenize_special_char.o\
				PARSER/scanner_function.o\
				\
				BUILTINS/echo.o\
				BUILTINS/env.o\
				BUILTINS/env_util.o\
				BUILTINS/export.o\
				BUILTINS/pwd.o\
				BUILTINS/unset.o\
				BUILTINS/cd.o\
				BUILTINS/exit.o\
				\
				EXECUTE/execute_command.o\
				# EXECUTE/execve.o
OBJS = ${addprefix SRC/, ${OBJS_FILES}}

SRCS = ${OBJS.o=.c}

# 사용하는 헤더들 여기에 추가
HEADER_FILES= minishell.h \
			  minishell_datastructrue.h
HEADERS = ${addprefix INC/, ${HEADER_FILES}}

all : ${NAME}

clean : 
		@make -C ./LIBFT clean
		${RM} ${OBJS}

fclean : clean
		@make -C ./LIBFT fclean
		${RM} ${NAME}

re : clean all

.PHONY : all clean fclean re

# 컴파일 옵션 다 써놔서 에러 뜰 덴데 걍 하면 됨
${NAME} : ${OBJS} ${LIBS}
		${CC} -o ${NAME} ${OBJS} ${LIBS} -lreadline \
		-L/Users/dkim2/.brew/Cellar/readline/8.1.2/lib \
		-I/Users/dkim2/.brew/Cellar/readline/8.1.2/include \
		-L/Users/yyoo/.brew/Cellar/readline/8.1.2/lib \
		-I/Users/yyoo/.brew/Cellar/readline/8.1.2/include

${LIBS} : 
		make -C ./LIBFT/ all


.c.o : ${HEADERS}
		${CC} ${CFLAGS} -c $< -o $@ \
		-I/Users/dkim2/.brew/Cellar/readline/8.1.2/include \
		-I/Users/yyoo/.brew/Cellar/readline/8.1.2/include
