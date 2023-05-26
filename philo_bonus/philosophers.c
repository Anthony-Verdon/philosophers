/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:57:47 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 16:59:34 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_philo *philo)
{
	while (1)
	{
		if (is_philo_dead(philo))
			break ;
		if (philo->state == THINKING)
			thinking(philo);
		else if (philo->state == EATING)
			eating(philo);
		else if (philo->state == SLEEPING)
			sleeping(philo);
	}
}

int	create_fork(int i, t_context *context)
{
	t_philo		philo;
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		init_philo(&philo, i, *context);
		routine(&philo);
		exit (0);
	}
	else if (pid < 0)
		return (1);
	else
		context->array_id[i] = pid;
	return (0);
}

void	close_semaphore(t_context *context)
{
	sem_close(context->forks);
	sem_close(context->priority);
	sem_close(context->print_program);
	sem_close(context->nb_philo_ate_required_meal);
	sem_close(context->one_philo_died);
}

int	main(int argc, char **argv)
{
	t_context	context;
	int			i;

	if (parsing(argc, argv) != 0)
		return (1);
	init_struct(argc, argv, &context);
	i = 0;
	while (i < context.nb_philo)
	{
		if (create_fork(i, &context) == 1)
			break ;
		i++;
	}
	create_thread(&context);
	i = 0;
	while (i < context.nb_philo)
	{
		waitpid(context.array_id[i], NULL, 0);
		i++;
	}
	free(context.array_id);
	close_semaphore(&context);
	return (0);
}
