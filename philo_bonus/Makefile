# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 11:23:44 by mprofett          #+#    #+#              #
#    Updated: 2023/06/20 09:01:12 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRC			= free_bonus.c init_structures_bonus.c main_bonus.c \
			routine_bonus.c routine_utils_bonus.c str_utils_bonus.c

OBJ			= ${SRC:.c=.o}

HEAD		= philo_bonus.h

CC			= gcc

RM			= rm -f

C_FLAGS	= -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${HEAD}
	${CC} $(C_FLAGS) ${OBJ} -o ${NAME}

clean:
	${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
