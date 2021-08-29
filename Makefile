NAME = minishell

CC = gcc
CCFLAGS = -Wall -Wextra -Werror

INCLUDES = ./includes

HEADER =	$(INCLUDES)/minishell.h \
			$(INCLUDES)/struct.h \
			$(INCLUDES)/parser.h \
			$(INCLUDES)/core.h \

HEADERS =	minitalk.h \
			struct.h \
			parser.h \
			core.h \

MAIN = main
PARSER = parse utils_1 quotes
CORE = init dict_utils

SRCS =	$(addsuffix .c, $(addprefix srcs/, $(MAIN))) \
		$(addsuffix .c, $(addprefix srcs/parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix srcs/core/, $(CORE))) \

OBJS = $(SRCS:.c=.o)

LIBFT_HEADER = ./libft/libft.h
LIBFT = ./libft/libft.a
LIBFT_FLAGS = -L=libft -lft

EXTLIB_FLAGS = -ltermcap -lreadline


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