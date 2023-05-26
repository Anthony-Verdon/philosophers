/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:57:52 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 14:42:58 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <semaphore.h> 
# include <sys/wait.h>
# include <fcntl.h>
# include "utils/utils.h"

# define EATING 1
# define START_THINKING 2
# define THINKING 3
# define SLEEPING 4
# define DEAD 5

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define MAGENTA "\e[35m"
# define DEFAULT "\e[39m"

typedef struct s_context {
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_to_eat;
	long			time_start_simulation;
	long			actual_time_simulation;
	int				*array_id;
	sem_t			*forks;
	sem_t			*one_philo_died;
	sem_t			*nb_philo_ate_required_meal;
	sem_t			*priority;
	sem_t			*print_program;
}	t_context;

typedef struct s_philo {
	int				id;
	int				state;
	int				nb_meal_eaten;
	int				last_meal_eat;
	int				nb_fork_hold;
	t_context		*context;
}	t_philo;

int		parsing(int argc, char **argv);
void	thinking(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
int		is_philo_dead(t_philo *philo);
long	calculate_time(void);
void	print_message(t_philo *philo);
void	ft_usleep(long time_to_wait, t_philo *philo);
void	init_struct(int argc, char **argv, t_context *context);
void	init_philo(t_philo *philo, int i, t_context context);
void	create_thread(t_context *context);
#endif
