/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:57:47 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 17:13:06 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_philo_dead(t_philo *philo)
{
	long	timestamp;

	timestamp = calculate_time() - philo->context->time_start_simulation;
	if (philo->state == DEAD)
		return (1);
	else if (timestamp - philo->last_meal_eat >= philo->context->time_to_die)
	{
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->context->check_philo_dead);
		print_message(philo);
		pthread_mutex_lock(&philo->context->check_philo_dead);
		philo->context->one_philo_is_dead = 1;
		return (1);
	}
	else
		return (0);
}

int	check_if_program_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->context->add_to_ate_required_meal);
	if (philo->context->nb_philo_ate_required_meal == philo->context->nb_philo)
	{
		if (philo->state == EATING)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(&philo->right_fork);
		}
		pthread_mutex_unlock(&philo->context->add_to_ate_required_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->context->add_to_ate_required_meal);
	pthread_mutex_lock(&philo->context->check_philo_dead);
	if (is_philo_dead(philo) || philo->context->one_philo_is_dead)
	{
		if (philo->state == EATING)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(&philo->right_fork);
		}
		pthread_mutex_unlock(&philo->context->check_philo_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->context->check_philo_dead);
	return (0);
}

void	*routine(void	*arg)
{
	t_philo	*philo;

	philo = (void *)arg;
	if (philo->id % 2 == 1)
		usleep(5000);
	while (1)
	{
		if (check_if_program_stop(philo) == 1)
			break ;
		if (philo->state == THINKING)
			thinking(philo);
		else if (philo->state == EATING)
			eating(philo);
		else if (philo->state == SLEEPING)
			sleeping(philo);
	}
	return (NULL);
}

void	start_program(t_context context, t_philo *philos, pthread_t *array_id)
{
	int	i;

	i = 0;
	while (i < context.nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].context = &context;
		pthread_mutex_init(&philos[i].right_fork, NULL);
		if (i == 0)
			philos[i].left_fork = &philos[context.nb_philo - 1].right_fork;
		else
			philos[i].left_fork = &philos[i - 1].right_fork;
		philos[i].state = THINKING;
		philos[i].last_meal_eat = 0;
		philos[i].nb_meal_eaten = 0;
		pthread_create(&array_id[i], NULL, &routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < context.nb_philo)
	{
		pthread_join(array_id[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_context	context;
	pthread_t	*array_id;
	t_philo		*philos;
	int			i;

	if (parsing(argc, argv) != 0)
		return (1);
	init_struct(argc, argv, &context);
	array_id = ft_calloc(context.nb_philo, sizeof(pthread_t));
	if (!array_id)
		return (2);
	philos = ft_calloc(context.nb_philo, sizeof(t_philo));
	if (!philos)
	{
		free(array_id);
		return (2);
	}
	start_program(context, philos, array_id);
	i = -1;
	while (++i < context.nb_philo)
		pthread_mutex_destroy(&philos[i].right_fork);
	pthread_mutex_destroy(&context.check_philo_dead);
	free(philos);
	free(array_id);
	return (0);
}
