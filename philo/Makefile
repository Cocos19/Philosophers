# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 11:23:44 by mprofett          #+#    #+#              #
#    Updated: 2023/06/20 08:57:15 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRC			= free.c main.c init_structures.c routine.c routine_utils.c \
			str_utils.c

OBJ			= ${SRC:.c=.o}

HEAD		= philo.h

CC			= gcc

RM			= rm -f

C_FLAGS	= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${HEAD}
	${CC} ${OBJ} -o ${NAME}

clean:
	${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
