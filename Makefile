NAME	=	ircserv

CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRCS	=	$(wildcard srcs/*.cpp \
			srcs/cmds/*.cpp \
			main.cpp)
OBJS	=	$(SRCS:.cpp=.o)

INCLUDES	= -I ./includes

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "$(NAME) has been created."

clean:
	@rm -f $(OBJS)
	@echo "$(NAME) binaries have been deleted."

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) has been deleted."

re: fclean all

.PHONY: all, clean, fclean, re
