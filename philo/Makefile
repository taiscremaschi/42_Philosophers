# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 13:24:31 by tbolzan-          #+#    #+#              #
#    Updated: 2024/02/19 14:23:55 by tbolzan-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

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