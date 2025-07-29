/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:56:16 by atran             #+#    #+#             */
/*   Updated: 2025/07/20 23:02:06 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_program *program)
{
	int	dead;

	pthread_mutex_lock(&program->dead_lock);
	dead = program->dead;
	pthread_mutex_unlock(&program->dead_lock);
	return (dead);
}

void	thinking(t_philo *philo)
{
	print_msg(philo->program, "is thinking", philo->id);
}

void	eating(t_philo *philo)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	if (philo->r_fork < philo->l_fork)
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	else
	{
		first = philo->l_fork;
		second = philo->r_fork;
	}
	pthread_mutex_lock(first);
	print_msg(philo->program, "has taken a fork", philo->id);
	pthread_mutex_lock(second);
	print_msg(philo->program, "has taken a fork", philo->id);
	print_msg(philo->program, "is eating", philo->id);
	pthread_mutex_lock(&philo->meals_lock);
	philo->times_eaten++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meals_lock);
	ft_usleep(philo->program, philo->program->time_to_eat);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

void	sleeping(t_philo *philo)
{
	print_msg(philo->program, "is sleeping", philo->id);
	ft_usleep(philo->program, philo->program->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->program, 1);
	while (!is_dead(philo->program))
	{
		thinking(philo);
		if (is_dead(philo->program))
			break ;
		if (philo->program->nb_philo == 1)
		{
			print_msg(philo->program, "has taken a fork", philo->id);
			break;
		}
		else
			eating(philo);
		if (is_dead(philo->program))
			break ;
		sleeping(philo);
	}
	return (NULL);
}
