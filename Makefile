NAME = ft_nm

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(PRINTF_PATH)/includes -I$(LIBFT_PATH)/includes -g

SRCS = 	srcs/main.c \
		srcs/parse_args.c \
		srcs/utils.c \
		srcs/parse_headers.c \
		srcs/extract_nm_32.c \
		srcs/extract_nm_64.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

PRINTF_PATH = ./ft_dprintf
PRINTF = $(PRINTF_PATH)/dprintf.a

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
WHITE = \033[0m

all: $(NAME)

#run command in the docker or do 'export LC_ALL=POSIX' in the terminal

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(PRINTF)

$(LIBFT):
	@echo -e "$(GREEN)Compiling the Libft ..."
	@make -sC $(LIBFT_PATH)
	@echo -e "$(GREEN)Compiling Complete !$(WHITE)"

$(PRINTF):
	@echo -e "$(GREEN)Compiling ft_printf ..."
	@make -sC $(PRINTF_PATH)
	@echo -e "$(GREEN)Compiling Complete !$(WHITE)"

clean:
	@echo -e "$(BLUE)Removing objects files ..."
	@make -sC $(LIBFT_PATH) clean
	@make -sC $(PRINTF_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo -e "$(BLUE)Removing Complete !$(WHITE)"

fclean: clean
	@echo -e "$(YELLOW)Removing archives and executables ..."
	@rm -f $(LIBFT)
	@rm -f $(PRINTF)
	@rm -f $(NAME)
	@echo -e "$(YELLOW)Removing Complete !$(WHITE)"

re: fclean all


.PHONY: all clean fclean re