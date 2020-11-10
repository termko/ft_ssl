NAME = ft_ssl
SRC = main.c sha256.c misc.c uint_rotate.c usage.c utils.c \
		md5/free.c md5/get_arrays.c md5/init.c md5/main_cycle.c \
		md5/output.c md5/parse_flags.c md5/prepare.c md5/read.c \
		md5/rounds.c md5/start.c
HDR = main.h

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	@gcc -o $(NAME) $(SRC) $(LIBFT) -Wall -Wextra -Werror

clean:

fclean: clean
	@rm -rf $(NAME)

re: fclean all