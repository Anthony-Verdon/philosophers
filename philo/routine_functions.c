/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:12:35 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 21:56:02 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->context->check_philo_dead);
	timestamp = calculate_time() - philo->context->time_start_simulation;
	if (!philo->context->one_philo_is_dead)
	{
		if (philo->state == THINKING)
			printf (MAGENTA"%ld %d has taken a fork\n"DEFAULT,
				timestamp, philo->id);
		else if (philo->state == EATING)
			printf (YELLOW"%ld %d is eating\n"DEFAULT, timestamp, philo->id);
		else if (philo->state == SLEEPING)
			printf (BLUE"%ld %d is sleeping\n"DEFAULT, timestamp, philo->id);
		else if (philo->state == START_THINKING)
			printf (GREEN"%ld %d is thinking\n"DEFAULT, timestamp, philo->id);
		else if (philo->state == DEAD)
			printf (RED"%ld %d died\n"DEFAULT, timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->context->check_philo_dead);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->context->check_philo_dead);
	print_message(philo);
	if (philo->context->nb_philo == 1)
	{
		ft_usleep(philo->context->time_to_die, philo);
		pthread_mutex_unlock(&philo->right_fork);
		is_philo_dead(philo);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->context->check_philo_dead);
	if (!is_philo_dead(philo))
	{
		pthread_mutex_unlock(&philo->context->check_philo_dead);
		print_message(philo);
		philo->state = EATING;
	}
	else
	{
		pthread_mutex_unlock(&philo->context->check_philo_dead);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->context->check_philo_dead);
	if (!is_philo_dead(philo))
		take_fork(philo);
	else
	{
		pthread_mutex_unlock(&philo->context->check_philo_dead);
		pthread_mutex_unlock(&philo->right_fork);
	}
}

void	eating(t_philo *philo)
{
	int	temp;

	print_message(philo);
	ft_usleep(philo->context->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_lock(&philo->context->check_philo_dead);
	if (!is_philo_dead(philo))
	{
		pthread_mutex_unlock(&philo->context->check_philo_dead);
		philo->nb_meal_eaten += 1;
		if (philo->nb_meal_eaten == philo->context->nb_meal_to_eat)
		{
			pthread_mutex_lock(&philo->context->add_to_ate_required_meal);
			philo->context->nb_philo_ate_required_meal += 1;
			pthread_mutex_unlock(&philo->context->add_to_ate_required_meal);
		}
		philo->state = SLEEPING;
		print_message(philo);
		temp = calculate_time() - philo->context->time_start_simulation;
		philo->last_meal_eat = temp;
	}
	else
		pthread_mutex_unlock(&philo->context->check_philo_dead);
}

void	sleeping(t_philo *philo)
{
	ft_usleep(philo->context->time_to_sleep, philo);
	pthread_mutex_lock(&philo->context->check_philo_dead);
	if (!is_philo_dead(philo))
	{
		philo->state = START_THINKING;
		pthread_mutex_unlock(&philo->context->check_philo_dead);
		print_message(philo);
		philo->state = THINKING;
	}
	else
		pthread_mutex_unlock(&philo->context->check_philo_dead);
}
