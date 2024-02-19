# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 17:48:55 by ricardo           #+#    #+#              #
#    Updated: 2023/12/19 18:07:23 by ricardo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

RM = rm -f

AR = ar -rsc

SRC = inicialize.c main.c utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) $(CFLAGS) -L. -o $(NAME)

%.o: %.c
	cc -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
	
.PHONE: all clean fclan re