/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:22:18 by atran             #+#    #+#             */
/*   Updated: 2025/07/20 23:00:15 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	to_num(const char *nptr, int sign)
{
	long int	check;
	int			num;

	num = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		check = num;
		if (check > check * 10)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		num = (num * 10) + (*nptr - '0');
		nptr++;
	}
	num = num * sign;
	return (num);
}

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;

	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	num = to_num(nptr, sign);
	return (num);
}

void	destroy_all(char *str, t_program *program, int exit_code)
{
	int	i;

	if (str)
		printf("%s\n", str);
	pthread_mutex_destroy(&program->print_lock);
	pthread_mutex_destroy(&program->dead_lock);
	i = 0;
	while (i < program->nb_philo)
	{
		pthread_mutex_destroy(&program->forks[i]);
		pthread_mutex_destroy(&program->philos[i].meals_lock);
		i++;
	}
	free(program->forks);
	free(program->philos);
	exit(exit_code);
}

void	print_msg(t_program *program, char *str, int id)
{
	size_t	time;

	time = get_time() - program->start_time;
	if (!is_dead(program))
	{
		pthread_mutex_lock(&program->print_lock);
		printf("%zu %d %s\n", time, id, str);
		pthread_mutex_unlock(&program->print_lock);
	}
}

void	ft_usleep(t_program *program, size_t duration)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < duration)
	{
		if (is_dead(program))
			break ;
		usleep(100);
	}
}
