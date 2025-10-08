/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:08:42 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/06 20:40:41 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_conf(t_config *conf, int argc, char **argv)
{
	conf->num_philos = ft_atoi_positive(argv[1]);
	conf->time_to_die = ft_atoi_positive(argv[2]);
	conf->time_to_eat = ft_atoi_positive(argv[3]);
	conf->time_to_sleep = ft_atoi_positive(argv[4]);
	if (argc == 6)
		conf->times_must_eat = ft_atoi_positive(argv[5]);
	else
		conf->times_must_eat = -1;
	conf->died = 0;
	conf->philos = malloc(sizeof(t_philo) * conf->num_philos);
	conf->forks = malloc(sizeof(pthread_mutex_t) * conf->num_philos);
	conf->threads = malloc(sizeof(pthread_t) * conf->num_philos);
	conf->meal_mutexes = malloc(sizeof(pthread_mutex_t) * conf->num_philos);
}

void	ft_init_philos(t_config *conf)
{
	int		i;
	long	start_time;

	i = 0;
	start_time = get_current_time();
	while (i < conf->num_philos)
	{
		conf->philos[i].id = i + 1;
		conf->philos[i].start_time = start_time;
		conf->philos[i].last_meal = start_time;
		conf->philos[i].left_fork = &conf->forks[i];
		conf->philos[i].right_fork = &conf->forks[(i + 1) % conf->num_philos];
		conf->philos[i].conf = conf;
		conf->philos[i].meal_mutex = &conf->meal_mutexes[i];
		i++;
	}
}

static void	init_death(t_config *conf)
{
	int	i;

	i = -1;
	while (++i < conf->num_philos)
		pthread_mutex_init(&conf->meal_mutexes[i], NULL);
	pthread_mutex_init(&conf->death_mutex, NULL);
}

void	ft_destroy(t_config conf)
{
	int	i;

	i = -1;
	while (++i < conf.num_philos)
		pthread_mutex_destroy(&conf.meal_mutexes[i]);
	pthread_mutex_destroy(&conf.death_mutex);
	free(conf.forks);
	free(conf.threads);
	free(conf.philos);
	free(conf.meal_mutexes);
}

int	main(int argc, char **argv)
{
	t_config	conf;
	int			i;

	i = -1;
	if (argc < 5 || argc > 6)
		return (printf("WRONG: Invalid number of arguments entered"), 1);
	ft_init_conf(&conf, argc, argv);
	while (++i < conf.num_philos)
		pthread_mutex_init(&conf.forks[i], NULL);
	init_death(&conf);
	ft_init_philos(&conf);
	i = -1;
	while (++i < conf.num_philos)
		pthread_create(&conf.threads[i], NULL, philo_routine, &conf.philos[i]);
	pthread_create(&conf.monitor_thread, NULL, monitor_routine, &conf);
	i = -1;
	while (++i < conf.num_philos)
		pthread_join(conf.threads[i], NULL);
	pthread_join(conf.monitor_thread, NULL);
	i = -1;
	while (++i < conf.num_philos)
		pthread_mutex_destroy(&conf.forks[i]);
	ft_destroy(conf);
	return (0);
}
