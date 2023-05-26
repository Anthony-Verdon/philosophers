/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:12:35 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 14:18:52 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo)
{
	long	timestamp;

	sem_wait(philo->context->print_program);
	timestamp = calculate_time() - philo->context->time_start_simulation;
	if (philo->state == THINKING)
		printf (MAGENTA"%ld %d has taken a fork\n"DEFAULT, timestamp, philo->id);
	else if (philo->state == EATING)
		printf (YELLOW"%ld %d is eating\n"DEFAULT, timestamp, philo->id);
	else if (philo->state == SLEEPING)
		printf (BLUE"%ld %d is sleeping\n"DEFAULT, timestamp, philo->id);
	else if (philo->state == START_THINKING)
		printf (GREEN"%ld %d is thinking\n"DEFAULT, timestamp, philo->id);
	else if (philo->state == DEAD)
		printf (RED"%ld %d died\n"DEFAULT, timestamp, philo->id);
	if (philo->state != DEAD)
		sem_post(philo->context->print_program);
}

void	take_fork(t_philo *philo)
{
	sem_wait(philo->context->priority);
	if (!is_philo_dead(philo))
	{
		sem_wait(philo->context->forks);
		if (!is_philo_dead(philo))
		{
			philo->nb_fork_hold += 1;
			print_message(philo);
			sem_wait(philo->context->forks);
			if (!is_philo_dead(philo))
			{
				print_message(philo);
				philo->nb_fork_hold += 1;
				philo->state = EATING;
				print_message(philo);
			}
		}
	}
	sem_post(philo->context->priority);
}

void	thinking(t_philo *philo)
{
	if (philo->context->nb_philo == 1)
	{
		ft_usleep(philo->context->time_to_die, philo);
		is_philo_dead(philo);
		return ;
	}
	else
		take_fork(philo);
}

void	eating(t_philo *philo)
{
	int	temp;

	ft_usleep(philo->context->time_to_eat, philo);
	sem_post(philo->context->forks);
	philo->nb_fork_hold -= 1;
	sem_post(philo->context->forks);
	philo->nb_fork_hold -= 1;
	if (!is_philo_dead(philo))
	{
		philo->nb_meal_eaten += 1;
		if (philo->nb_meal_eaten == philo->context->nb_meal_to_eat)
			sem_post(philo->context->nb_philo_ate_required_meal);
		philo->state = SLEEPING;
		print_message(philo);
		temp = calculate_time() - philo->context->time_start_simulation;
		philo->last_meal_eat = temp;
	}
}

void	sleeping(t_philo *philo)
{
	ft_usleep(philo->context->time_to_sleep, philo);
	if (!is_philo_dead(philo))
	{
		philo->state = START_THINKING;
		print_message(philo);
		philo->state = THINKING;
	}
}
