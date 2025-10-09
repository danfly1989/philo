/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:49:54 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/09 13:49:59 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meal_mutex;
	int				time_to_eat;
	long			start_time;
	long			last_meal;
	int				times_eaten;
	struct s_config	*conf;
}					t_philo;

typedef struct s_config
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				died;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meal_mutexes;
	pthread_mutex_t	print_mutex;
	pthread_t		*threads;
	pthread_t		monitor_thread;
	t_philo			*philos;
}					t_config;

void				*philo_routine(void *arg);
int					ft_atoi_positive(char *str);
void				ft_init_conf(t_config *conf, int argc, char **argv);
long				get_current_time(void);
void				ft_sleep(long milliseconds);
void				*monitor_routine(void *arg);
void				ft_print(t_philo *philo, char *message);
int					check_death(t_philo *philo);
void				ft_print_think(t_philo *philo);
void				ft_print_eat(t_philo *philo);
void				ft_print_sleep(t_philo *philo);
void				ft_print_fork(t_philo *philo);
void				ft_print_die(t_philo *philo);

#endif
