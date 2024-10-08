SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_strlen.c \
		ft_isalpha.c ft_isdigit.c ft_strchr.c ft_atoi.c\
		ft_strrchr.c ft_strncmp.c ft_strcmp.c ft_calloc.c\
		ft_putstr_fd.c ft_putendl_fd.c ft_lstnew.c\
		ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
		ft_lstadd_back_bonus.c ft_lstclear_bonus.c\
		ft_itoa_mini.c ft_lstnew_mini.c ft_strdup_mini.c\
		ft_strjoin_mini.c ft_split_mini.c ft_substr_mini.c

OBJ = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	ar -rcs $(NAME) $?

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY:  all clean fclean re