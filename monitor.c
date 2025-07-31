/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:56:16 by atran             #+#    #+#             */
/*   Updated: 2025/07/28 18:25:19 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_die_msg(t_program *program, char *str, int id)
{
	size_t	time;

	time = get_time() - program->start_time;
	pthread_mutex_lock(&program->print_lock);
	printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(&program->print_lock);
}

int	check_if_die(t_program *program)
{
	int		i;
	size_t	time_since_last_eat;

	i = 0;
	while (i < program->nb_philo)
	{
		pthread_mutex_lock(&program->philos[i].meals_lock);
		time_since_last_eat = get_time() - program->philos[i].last_meal;
		pthread_mutex_unlock(&program->philos[i].meals_lock);
		if (time_since_last_eat > program->time_to_die)
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead = 1;
			pthread_mutex_unlock(&program->dead_lock);
			print_die_msg(program, "DIED", program->philos[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_ate(t_program *program)
{
	int	i;
	int	enough_eat;

	i = 0;
	enough_eat = 0;
	if (program->times_must_eat == 0)
		return (0);
	while (i < program->nb_philo)
	{
		pthread_mutex_lock(&program->philos[i].meals_lock);
		if (program->philos[i].times_eaten >= program->times_must_eat)
			enough_eat++;
		pthread_mutex_unlock(&program->philos[i].meals_lock);
		i++;
	}
	if (enough_eat == program->nb_philo)
	{
		pthread_mutex_lock(&program->dead_lock);
		program->dead = 1;
		pthread_mutex_unlock(&program->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	ft_usleep(program, program->time_to_die * 0.8);
	while (1)
	{
		if (check_all_ate(program) || check_if_die(program))
			break ;
		ft_usleep(program, 5);
	}
	return (NULL);
}
