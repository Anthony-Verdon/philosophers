SRCS ?=	srcs/philo/philosophers.c \
		srcs/philo/routine_functions.c \
		srcs/philo/parsing.c \
		srcs/philo/utils.c \
		srcs/philo/utils/ft_atoll.c \
		srcs/philo/utils/ft_isdigit.c \
		srcs/philo/utils/ft_calloc.c

BSRCS ?=	srcs/philo_bonus/philosophers.c \
		srcs/philo_bonus/thread.c \
		srcs/philo_bonus/routine_functions.c \
		srcs/philo_bonus/parsing.c \
		srcs/philo_bonus/utils.c \
		srcs/philo_bonus/utils/ft_atoll.c \
		srcs/philo_bonus/utils/ft_isdigit.c \
		srcs/philo_bonus/utils/ft_calloc.c
		
OBJS ?= ${SRCS:.c=.o}

NAME ?= philo

BOBJS ?= ${BSRCS:.c=.o}

NAME_BONUS ?= philo_bonus

COMPILER ?= clang

RM		?= rm -f

CFLAGS 	?= -Wall -Werror -Wextra -g

LIBRARY ?= -pthread

.c.o:		${OBJS}
			${COMPILER} ${CFLAGS} -c $< -o ${<:.c=.o}

all: 		${NAME}

bonus: 		${NAME_BONUS}

${NAME}:	${OBJS}
			${COMPILER} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBRARY}

${NAME_BONUS}:	${BOBJS}
			${COMPILER} ${CFLAGS} ${BOBJS} -o ${NAME_BONUS}
			
clean:
			${RM} ${OBJS} ${BOBJS}

fclean: 	clean
			${RM} ${NAME} ${NAME_BONUS}

re:
			make fclean
			make

.PHONY: 	all bonus clean fclean re bonus
