SRCS ?=	philosophers.c \
		routine_functions.c \
		parsing.c \
		utils.c \
		utils/ft_atoll.c \
		utils/ft_isdigit.c \
		utils/ft_calloc.c

OBJS ?= ${SRCS:.c=.o}

NAME ?= philo

COMPILER ?= clang

RM		?= rm -f

CFLAGS 	?= -Wall -Werror -Wextra -g

LIBRARY ?= -pthread

.c.o:		${OBJS}
			${COMPILER} ${CFLAGS} -c $< -o ${<:.c=.o}

all: 		${NAME}

${NAME}:	${OBJS}
			${COMPILER} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBRARY}

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re:
			make fclean
			make

.PHONY: 	all bonus clean fclean re
