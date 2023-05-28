/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:22:36 by averdon           #+#    #+#             */
/*   Updated: 2023/01/30 20:50:36 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

void	*check_philo_dead(void *arg)
{
	int			i;
	t_context	*context;

	context = (t_context *)arg;
	sem_wait(context->one_philo_died);
	i = 0;
	while (i < context->nb_philo)
	{
		kill(context->array_id[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < context->nb_philo)
	{
		sem_post(context->nb_philo_ate_required_meal);
		i++;
	}
	sem_post(context->priority);
	sem_post(context->print_program);
	return (NULL);
}

void	*check_philo_nb_meal(void *arg)
{
	int			i;
	t_context	*context;

	context = (t_context *)arg;
	i = 0;
	while (i < context->nb_philo)
	{
		sem_wait(context->nb_philo_ate_required_meal);
		i++;
	}
	sem_wait(context->priority);
	sem_wait(context->print_program);
	i = 0;
	while (i < context->nb_philo)
	{
		kill(context->array_id[i], SIGKILL);
		i++;
	}
	sem_post(context->one_philo_died);
	return (NULL);
}

void	create_thread(t_context *context)
{
	pthread_t	thread_death;
	pthread_t	thread_meal;

	pthread_create(&thread_death, NULL, check_philo_dead, context);
	pthread_join(thread_death, NULL);
	if (context->nb_meal_to_eat != -1)
	{
		pthread_create(&thread_meal, NULL, check_philo_nb_meal, context);
		pthread_join(thread_meal, NULL);
	}
}
