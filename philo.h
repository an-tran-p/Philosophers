/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:34:35 by atran             #+#    #+#             */
/*   Updated: 2025/07/20 23:02:19 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					times_eaten;
	size_t				last_meal;
	pthread_mutex_t		meals_lock;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	struct s_program	*program;
}						t_philo;

typedef struct s_program
{
	pthread_t			monitor;
	t_philo				*philos;
	size_t				start_time;
	int					nb_philo;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					times_must_eat;
	int					dead;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		dead_lock;
}						t_program;

int						ft_atoi(const char *nptr);
int						check_valid_args(char **argv);
size_t					get_time(void);
int						init_program(t_program *p, char **argv);
void					*monitoring(void *arg);
void					*routine(void *arg);
void					ft_usleep(t_program *program, size_t duration);
void					print_msg(t_program *program, char *str, int id);
int						is_dead(t_program *program);
void					destroy_all(char *str, t_program *program,
							int exit_code);

#endif