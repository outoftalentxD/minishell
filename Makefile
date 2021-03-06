NAME = minishell

CC = gcc 
CFLAGS = -Wextra -Wall -Werror

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
PARSER = parse quotes utils_1 utils_2 section section_utils section_types
CORE = init dict_utils dict_utils_2 exec_command binary signal utils validator clean env_utils
BUILTINS = echo pwd env export cd unset exit
PIPE = pipe utils redirect redirect_utils

SRCS =	$(addsuffix .c, $(addprefix srcs/, $(MAIN))) \
		$(addsuffix .c, $(addprefix srcs/parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix srcs/core/, $(CORE))) \
		$(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix srcs/pipe/, $(PIPE))) \

OBJS = $(SRCS:.c=.o)

LIBFT_HEADER = ./libft/libft.h
LIBFT = ./libft/libft.a
LIBFT_FLAGS = -L libft -lft
MAC_LIBFT_FLAGS = -L libft -lft

USR = $(shell whoami)

LRD_INC =   -I/Users/$(USR)/.brew/opt/readline/include
LLRD_INC =  -I/usr/local/Cellar/readline/8.1/include
LRD_LIB =   -lreadline -L/Users/$(USR)/.brew/opt/readline/lib
LLRD_LIB =  -lreadline -L/usr/local/Cellar/readline/8.1/lib

EXTLIB_FLAGS = -ltermcap -lreadline


$(NAME): 

$(OBJS): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) $(LRD_INC) -o $@

$(LIBFT):
	$(MAKE) -C ./libft

all: $(NAME)

minishell: $(OBJS) $(LIBFT) $(HEADER) 
	$(CC) $(OBJS) $(LIBFT_FLAGS) $(EXTLIB_FLAGS) $(LRD_LIB) -o $@

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