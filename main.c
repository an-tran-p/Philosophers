/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:56:16 by atran             #+#    #+#             */
/*   Updated: 2025/07/12 16:26:08 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_n_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || check_n_digit(argv[1]))
		return (printf("Invalid number of philosophers\n"), 1);
	if (ft_atoi(argv[2]) <= 0 || check_n_digit(argv[2]))
		return (printf("Invalid time_to_die\n"), 1);
	if (ft_atoi(argv[3]) <= 0 || check_n_digit(argv[3]))
		return (printf("Invalid time_to_eat\n"), 1);
	if (ft_atoi(argv[4]) <= 0 || check_n_digit(argv[4]))
		return (printf("Invalid time_to_sleep\n"), 1);
	if (argv[5])
	{
		if (ft_atoi(argv[5]) < 0 || check_n_digit(argv[5]))
			return (printf("Invalid time_must_eat\n"), 1);
		if (ft_atoi(argv[5]) == 0)
			exit(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Wrong arguments count\n"), 1);
	else if (check_valid_args(argv))
		return (1);
}
