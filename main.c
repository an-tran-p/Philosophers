/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:56:16 by atran             #+#    #+#             */
/*   Updated: 2025/07/20 23:01:58 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creating_threads(t_program *program)
{
	int	i;

	if (pthread_create(&program->monitor, NULL, &monitoring, program))
		destroy_all("Failed creating thread", program, 1);
	i = 0;
	while (i < program->nb_philo)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine,
				&program->philos[i]))
			destroy_all("Failed creating thread", program, 1);
		i++;
	}
	if (pthread_join(program->monitor, NULL))
		destroy_all("Failed joining thread", program, 1);
	i = 0;
	while (i < program->nb_philo)
	{
		if (pthread_join(program->philos[i].thread, NULL))
			destroy_all("Failed creating thread", program, 1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc != 5 && argc != 6)
		return (printf("Wrong arguments count\n"), 1);
	else if (check_valid_args(argv))
		return (1);
	if (init_program(&program, argv))
		return (1);
	creating_threads(&program);
	destroy_all(NULL, &program, 0);
	return (0);
}
