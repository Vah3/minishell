# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 16:05:05 by vagevorg          #+#    #+#              #
#    Updated: 2022/08/31 18:39:54 by vagevorg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc *.c -lft -LLibft -lreadline -o minishell 

NAME			= minishell

CC				= cc

CFLAGS			= -Wall -Wextra #-Werror -g -ggdb3

RM				= rm -f

SRCS			= $(wildcard *.c )

OBJS			= $(SRCS:.c=.o)

LIBFT			= -C Libft/

CLE				= make clean

FCLE			= make fclean

INCLUDES		= -ILibft -I/usr/local/include

LINKERS			= -lft -lreadline -L./Libft

%.o:%.c
				@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(MAKE) $(LIBFT)
				@$(CC) $(CFLAGS) $(OBJS) $(LINKERS) $(INCLUDES) -o $(NAME)
				@echo "\033[1;31m Minishel created \033[0m"

clean:
				@$(RM) $(OBJS)
				@$(CLE) $(LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@$(FCLE) $(LIBFT)

re:				fclean all

.PHONY:			all clean fclean re
