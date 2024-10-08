SRC = 	main.c\
		utils/utils1.c\
		utils/utils2.c\
		utils/utils3.c\
		errors/errors1.c\
		errors/errors2.c\
		builtins/builtins_cd.c \
		builtins/builtins_echo_pwd.c\
		builtins/builtins_exit_env.c\
		builtins/builtins_export.c\
		builtins/builtins_export2.c\
		builtins/export_utils.c\
		builtins/builtins_unset.c\
		builtins/builtins.c\
		exec/execution1.c\
		exec/execution2.c\
		exec/pipes.c\
		exec/search_path.c\
		exec/redirictions.c\
		expand/expand_utils.c\
		expand/expand_utils2.c\
		expand/expand.c\
		parsing/here_doc.c\
		parsing/heredoc_utils.c\
		parsing/lexer1.c\
		parsing/lexer2.c\
		parsing/parser1.c\
		parsing/parser2.c\
		parsing/parser3.c\
		parsing/parser4.c\


OBJ = $(SRC:.c=.o)

NAME = ../minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

LIBFT = ../libft/libft.a

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re














