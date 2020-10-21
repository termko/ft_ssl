NAME = ft_ssl
SRC = main.c sha256.c md5.c base64.c
HDR = main.h

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	@gcc -o $(NAME) $(SRC) $(LIBFT) -Wall -Wextra -Werror

clean:

fclean: clean
	@rm -rf $(NAME)

re: fclean all