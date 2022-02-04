# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/21 17:21:01 by cboutier          #+#    #+#              #
#    Updated: 2021/11/21 15:22:40 by cboutier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	= srcs

NAMES		= philo.c philo_utils.c \
			parsing.c utils.c \
			threads.c \
			time.c \
			actions.c \
			free.c

SRCS		= $(addprefix $(SRCS_DIR)/, $(NAMES))

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -pthread

INCLUDES	= -I incl/

OBJS		= ${SRCS:.c=.o}

NAME		= philo

RM			= rm -f

.c.o:
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all re clean fclean