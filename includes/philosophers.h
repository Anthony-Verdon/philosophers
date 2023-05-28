/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:57:52 by averdon           #+#    #+#             */
/*   Updated: 2023/05/28 18:12:32 by averdon          ###   ########.fr       */
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
# include "utils.h"

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
	pthread_mutex_t	check_philo_dead;
	bool			one_philo_is_dead;
	pthread_mutex_t	add_to_ate_required_meal;
	int				nb_philo_ate_required_meal;
}	t_context;

typedef struct s_philo {
	int				id;
	int				state;
	int				nb_meal_eaten;
	int				last_meal_eat;
	t_context		*context;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
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
#endif
