NAME = dprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes

SRCS =	srcs/ft_dprintf.c srcs/ft_char.c srcs/ft_putchar_fd_printf.c srcs/ft_putstr_fd_printf.c \
		srcs/ft_putnbr_fd_printf.c srcs/ft_str.c srcs/ft_strlen.c srcs/ft_ptr.c srcs/ft_putnbr_unsigned_fd.c \
		srcs/ft_hex.c srcs/convert_hex.c

OBJS_DIR = objs

OBJS =	$(SRCS:%.c=$(OBJS_DIR)/%.o)

$(OBJS_DIR)/%.o:%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rsc $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
