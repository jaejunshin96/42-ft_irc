NAME	=	ircserv

CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRCS	=	$(wildcard srcs/*.cpp \
			srcs/cmds/*.cpp \
			main.cpp)
OBJS	=	$(SRCS:.cpp=.o)

INCLUDES	= -I ./incldues

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "ircserv has been created."

clean:
	@rm -f $(OBJS)
	@echo "ircserv binaries have been deleted."

fclean: clean
	@rm -f $(NAME)
	@echo "ircserv has been deleted."

re: fclean all

.PHONY: all, clean, fclean, re
