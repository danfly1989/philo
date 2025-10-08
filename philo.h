#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

//forward declaration
typedef struct s_data t_data;

typedef struct s_philo
{
	int id;
	int meals_eaten;
	long last_meal_time;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data
}	t_philo

typedef struct s_data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_eat;
	long	start_timel
	int	dead;
	pthread_mutex_t *forks;
	pthread_mutex_t write_lock;
	pthread_mutex_t death_lock;
	t_philo *philos;
}	t_data;

int	ft_atoi_positive(char *str);
int	init_data(t_data *data, ubt argc, char **argv);
void	cleanup_data(t_data *data);

#endif
