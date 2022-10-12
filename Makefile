# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vagevorg <vagevorg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 16:05:05 by vagevorg          #+#    #+#              #
#    Updated: 2022/10/12 20:52:44 by vagevorg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


PREFIX			= $(shell find ${HOME} -name readline-edgghaza 2>/dev/null)

NAME			= minishell

CC				= cc

CFLAGS			= -Wall -Wextra -g -ggdb3 -Werror #-fsanitize=address

RM				= rm -f

SRCS			= $(wildcard *.c )

OBJS			= $(SRCS:.c=.o)

LIBFT			= -C Libft/

CLE				= make clean

FCLE			= make fclean

INCLUDES		= -ILibft  -I./readline-edgghaza/include

LINKERS			=  -L./Libft -L./readline-edgghaza/lib -lft -lreadline

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

readline:
	cd readline-master && make clean && ./configure --prefix=$(PREFIX) && make && make install

.PHONY:			all clean fclean re readline
