# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/26 16:41:56 by mmuhaise          #+#    #+#              #
#    Updated: 2024/09/11 05:19:14 by mmuhaise         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main utils/utils utils/heredoc utils/path utils/utils_extended quotations/quotations \
		quotations/expansion quotations/quotations_utils utils/utils_extra utils/heredoc_extended

EXEC_SRCS = exec/execution exec/pipe_execution exec/sc_execution exec/exec_utils

BUILT_SRCS = builtins/builtins builtins/env builtins/export builtins/export_extended builtins/unset builtins/exit builtins/echo

PARSER_SRCS = parsing/parsing parsing/parsing_extended parsing/parsing_utils parsing/ast

TOKEN_SRCS = tokenize/tokenization tokenize/tokenization_extended tokenize/tokenization_utils

SRC = $(addsuffix .c, $(addprefix src/, $(SRCS)))
EXEC_SRC = $(addsuffix .c, $(addprefix src/, $(EXEC_SRCS)))
BUILT_SRC = $(addsuffix .c, $(addprefix src/, $(BUILT_SRCS)))
PARSER_SRC = $(addsuffix .c, $(addprefix src/, $(PARSER_SRCS)))
TOKEN_SRC = $(addsuffix .c, $(addprefix src/, $(TOKEN_SRCS)))

OBJS = $(addsuffix .o, $(addprefix objs/, $(SRCS)))
EXEC_OBJS = $(addsuffix .o, $(addprefix objs/, $(EXEC_SRCS)))
BUILT_OBJS = $(addsuffix .o, $(addprefix objs/, $(BUILT_SRCS)))
PARSER_OBJS = $(addsuffix .o, $(addprefix objs/, $(PARSER_SRCS)))
TOKEN_OBJS = $(addsuffix .o, $(addprefix objs/, $(TOKEN_SRCS)))

LIBFT_DIR = ./libft

LIBFT_LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(EXEC_OBJS) $(BUILT_OBJS) $(PARSER_OBJS) $(TOKEN_OBJS)
	make -C $(LIBFT_DIR)
	gcc  -g -Wall -Wextra -Werror $(OBJS) $(EXEC_OBJS) $(BUILT_OBJS) $(PARSER_OBJS) $(TOKEN_OBJS) -o $(NAME) $(LIBFT_LIB) -lreadline

objs/%.o:	src/%.c
	@mkdir -p $(dir $@)
	@gcc -g -Wall -Wextra -Werror -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf ./objs

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re