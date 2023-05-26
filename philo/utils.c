/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:10:14 by averdon           #+#    #+#             */
/*   Updated: 2023/01/16 17:28:53 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	calculate_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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
	pthread_mutex_init(&context->check_philo_dead, NULL);
	context->one_philo_is_dead = 0;
	pthread_mutex_init(&context->add_to_ate_required_meal, NULL);
	context->nb_philo_ate_required_meal = 0;
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
		pthread_mutex_lock(&philo->context->check_philo_dead);
		if (is_philo_dead(philo) || philo->context->one_philo_is_dead)
		{
			pthread_mutex_unlock(&philo->context->check_philo_dead);
			break ;
		}
		pthread_mutex_unlock(&philo->context->check_philo_dead);
	}
}
