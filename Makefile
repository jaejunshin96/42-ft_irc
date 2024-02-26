NAME	= ircserv

CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98

SRCS	= srcs/*.cpp main.cpp

$(NAME):
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "ircserv has been created."

all: $(NAME)

clean:
	@rm -f $(NAME)
	@echo "ircserv has been deleted."

fclean: clean

re: fclean all

.PHONY: all, clean, fclean, re
