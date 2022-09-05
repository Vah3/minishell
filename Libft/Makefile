# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 15:17:43 by vagevorg          #+#    #+#              #
#    Updated: 2022/08/27 17:46:48 by vagevorg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

SRCS		= $(wildcard *.c) 

#BSRCS		= $(wildcard ft_lst*.c)

OBJS 		= $(SRCS:.c=.o)

#BOBJS		= $(BSRCS:.c=.o)


%.o:%.c
			@$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

#bonus:		$(BOBJS)
#			@ar rcs $(NAME) $(BOBJS)

clean:
			@$(RM) $(OBJS) 
#			@$(RM) $(BOBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY: 	all bouns clean fclean re
