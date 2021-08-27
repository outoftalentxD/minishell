NAME = minishell

CC = clang

CCFLAGS = -Wall -Wextra -Werror

INCLUDES = ./includes

HEADER =	$(INCLUDES)/minishell.h \
			$(INCLUDES)/struct.h

HEADERS =	minitalk.h \
			struct.h

SRCS =	srcs/main.c \

OBJS = $(SRCS:.c=.o)

LIBFT_HEADER = ./libft/libft.h
LIBFT = ./libft/libft.a
LIBFT_FLAGS = -L=libft -lft

EXTLIB_FLAGS = -ltermcap 

$(NAME): 

$(OBJS): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(LIBFT):
	$(MAKE) -C ./libft

all: $(NAME)

minishell: $(OBJS) $(LIBFT) $(HEADER) 
	$(CC) $(OBJS) $(LIBFT_FLAGS) $(EXTLIB_FLAGS) -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C ./libft

fclean: clean
	$(RM) minishell
	$(MAKE) fclean -C ./libft

re:
	$(MAKE) fclean
	$(MAKE) all

norm:
	norminette $(SRC) | grep "Error"
	norminette $(INCLUDES) | grep "Error"