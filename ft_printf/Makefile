CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRC = ft_printf.c \
		print_char.c print_hex.c  print_nbr.c \
		print_ptr.c  print_str.c  print_unsignedint.c

OBJ = $(SRC:.c=.o)

HEADER = libftprintf.h

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH) all

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
