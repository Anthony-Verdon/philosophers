/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:10:14 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 14:21:53 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

long	calculate_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time_to_wait, t_philo *philo)
{
	long	time_start_usleep;
	long	actual_time;

	time_start_usleep = calculate_time();
	actual_time = calculate_time();
	while (actual_time - time_start_usleep < time_to_wait)
	{
		usleep(500);
		actual_time = calculate_time();
		if (is_philo_dead(philo))
			break ;
	}
}

int	is_philo_dead(t_philo *philo)
{
	long	timestamp;

	timestamp = calculate_time() - philo->context->time_start_simulation;
	if (philo->state == DEAD)
	{
		sem_post(philo->context->one_philo_died);
		return (1);
	}
	else if (timestamp - philo->last_meal_eat >= philo->context->time_to_die)
	{
		philo->state = DEAD;
		print_message(philo);
		sem_post(philo->context->one_philo_died);
		sem_wait(philo->context->priority);
		return (1);
	}
	else
		return (0);
}

void	init_philo(t_philo *philo, int i, t_context context)
{
	philo->id = i + 1;
	if (philo->id % 2 == 1)
		philo->state = SLEEPING;
	else
		philo->state = THINKING;
	philo->last_meal_eat = 0;
	philo->nb_meal_eaten = 0;
	philo->context = &context;
	philo->nb_fork_hold = 0;
}

void	init_struct(int argc, char **argv, t_context *context)
{
	(void)argc;
	context->nb_philo = ft_atoll(argv[1]);
	context->time_to_die = ft_atoll(argv[2]);
	context->time_to_eat = ft_atoll(argv[3]);
	context->time_to_sleep = ft_atoll(argv[4]);
	if (argv[5])
		context->nb_meal_to_eat = ft_atoll(argv[5]);
	else
		context->nb_meal_to_eat = -1;
	context->time_start_simulation = calculate_time();
	context->actual_time_simulation = calculate_time();
	context->array_id = ft_calloc(context->nb_philo, sizeof(int));
	sem_unlink("fork");
	context->forks = sem_open("fork", O_CREAT, 660, context->nb_philo);
	sem_unlink("one is dead");
	context->one_philo_died = sem_open("one is dead", O_CREAT, 660, 0);
	sem_unlink("nb philo ate");
	context->nb_philo_ate_required_meal = sem_open("nb philo ate",
			O_CREAT, 660, 0);
	sem_unlink("priority");
	context->priority = sem_open("priority", O_CREAT, 660, 1);
	sem_unlink("print");
	context->print_program = sem_open("print", O_CREAT, 660, 1);
}
