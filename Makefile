SRCS = srcs

NAME = minishell

LIBFT = libft

all :
	make -C $(LIBFT)
	make -C $(SRCS)

clean :
	make clean -C $(LIBFT)
	make clean -C $(SRCS)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re : fclean all

.PHONY:  all clean fclean re