NAME	= client

CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98

SRCS	= client.cpp

$(NAME):
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "client has been created."

all: $(NAME)

clean:
	@rm -f $(NAME)
	@echo "client has been deleted."

fclean: clean

re: fclean all

.PHONY: all, clean, fclean, re
