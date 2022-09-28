# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 16:05:05 by vagevorg          #+#    #+#              #
#    Updated: 2022/09/24 20:16:04 by vagevorg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc *.c -lft -LLibft -lreadline -o minishell 

NAME			= minishell

CC				= cc

CFLAGS			= -Wall -Wextra -g -ggdb3 #-Werror 

RM				= rm -f

SRCS			= $(wildcard *.c )

OBJS			= $(SRCS:.c=.o)

LIBFT			= -C Libft/

CLE				= make clean

FCLE			= make fclean

INCLUDES		= -ILibft  -I/Users/vagevorg/readline/include

LINKERS			=  -L./Libft -L/Users/vagevorg/readline/lib -lft -lreadline

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
