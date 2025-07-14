/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:56:16 by atran             #+#    #+#             */
/*   Updated: 2025/07/14 22:27:51 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_philos(t_philo *philos, t_program *p)
{
	int	i;

	i = 0;
	while (i < p->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].times_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].r_fork = &p->forks[i];
		philos[i].l_fork = &p->forks[(i + 1) % p->nb_philo];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, t_program *p)
{
	int	i;

	i = 0;
	while (i < p->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

int	init_program(t_program *p, char **argv)
{
	p->start_time = get_time();
	p->nb_philo = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		p->time_must_eat = ft_atoi(argv[5]);
	else
		p->time_must_eat = 0;
	p->died = 0;
	p->philos = malloc(p->nb_philo * sizeof(t_philo));
	if (!p->philos)
		return (1);
	p->forks = malloc(p->nb_philo * sizeof(pthread_mutex_t));
	if (!p->forks)
		return (free(p->philos), 1);
	init_philos(p->philos, p);
	init_forks(p->forks, p);
	pthread_mutex_init(&p->print, NULL);
	pthread_mutex_init(&p->dead_lock, NULL);
	return (0);
}
