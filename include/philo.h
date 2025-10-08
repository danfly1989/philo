/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:00:33 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/07 17:02:02 by daflynn          ###   ########.fr       */
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
void				*monitor_routine(void *arg);
#endif
