# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylr <ylr@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 18:40:00 by oubelhaj          #+#    #+#              #
#    Updated: 2023/08/03 23:41:52 by ylr              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = ./src/minishell.c ./src/parsing/file_opening.c ./src/parsing/lexer.c ./src/parsing/parser.c \
	./src/parsing/initialization.c ./src/parsing/error_handling.c ./src/parsing/expansion.c \
	./src/parsing/here_doc.c ./includes/helpers/ft_atoi.c ./includes/helpers/ft_is_whitespace.c ./includes/helpers/ft_isalnum.c \
	./includes/helpers/ft_isalpha.c ./includes/helpers/ft_isdigit.c ./includes/helpers/ft_putchar_fd.c ./includes/helpers/ft_putnbr_fd.c \
	./includes/helpers/ft_putstr_fd.c ./includes/helpers/ft_exit_error.c ./includes/helpers/ft_putendl.c ./includes/linked_lists/ft_lstadd_back.c \
	./includes/linked_lists/ft_lstclear.c ./includes/linked_lists/ft_lstdelone.c ./includes/linked_lists/ft_lstlast.c \
	./includes/linked_lists/ft_lstnew.c ./includes/linked_lists/ft_lstsize.c ./includes/string_helpers/ft_free_strs.c \
	./includes/string_helpers/ft_split.c ./includes/string_helpers/ft_strdup.c ./includes/string_helpers/ft_strjoin.c \
	./includes/string_helpers/ft_strlen.c ./includes/string_helpers/ft_strstr.c ./includes/string_helpers/ft_strnstr.c \
	./includes/string_helpers/ft_strncmp.c ./includes/string_helpers/ft_strcmp.c ./includes/string_helpers/ft_substr.c \
	./includes/string_helpers/ft_strchr.c ./includes/string_helpers/index_at.c ./includes/get_next_line/get_next_line.c ./includes/get_next_line/get_next_line_utils.c \
	./includes/linked_lists/ft_lstadd_back_alt.c ./includes/linked_lists/ft_last_env.c ./includes/linked_lists/ft_lstnew_alt.c ./includes/linked_lists/ft_lstlast_alt.c \
	./includes/helpers/get_env.c ./includes/helpers/search_in_env.c ./includes/linked_lists/ft_lstadd_back_env.c ./includes/linked_lists/ft_lstnew_env.c \
	./src/builtins/cd.c ./src/builtins/exit.c ./src/builtins/unset.c ./src/builtins/pwd.c ./src/builtins/env.c ./src/builtins/echo.c ./src/builtins/export.c ./includes/linked_lists/ft_lstclear_env.c ./includes/linked_lists/ft_lstdelone_env.c \
	./includes/linked_lists/ft_lstadd_back_reds.c ./includes/linked_lists/ft_lstlast_reds.c ./includes/linked_lists/ft_lstnew_reds.c ./includes/linked_lists/ft_lstclear_reds.c \
	./includes/string_helpers/ft_count_strs.c ./src/builtins/builtins.c ./src/parsing/lexer_handlers.c ./src/parsing/lexer_handlers2.c ./src/parsing/lexer_utils.c \
	./includes/helpers/is_quotes.c ./includes/helpers/is_redirection.c ./src/execution/error_handler.c ./src/execution/pipes_handler.c ./src/execution/executor.c ./src/parsing/heredoc_expand.c \
	./includes/string_helpers/ft_itoa.c
	

OBJS = ${SRC:.c=.o}

CC = cc

CFLAGS = -fsanitize=address -g3

.c.o	:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
	@echo "\033[1;32m- minishell compiled!\033[0m"

clean :
	@rm -rf $(OBJS)
	@echo "\033[1;33m- Object files removed!\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[1;31m- minishell deleted!\033[0m"

re : fclean all