NAME = philo

CC = cc
CFLAGS= -Wall -Wextra -Werror

SRC_DIR = src/
SRC_FILES = main.c init.c helper.c simulation.c delete.c

INCLUDE_DIR = ./include
INCLUDE = -I$(INCLUDE_DIR)

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
