/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:06:12 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/07 17:06:28 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_config	*conf;
	int			i;
	long		current_time;

	conf = (t_config *)arg;
	while (1)
	{
		i = -1;
		while (++i < conf->num_philos)
		{
			pthread_mutex_lock(conf->philos[i].meal_mutex);
			current_time = get_current_time();
			if (current_time - conf->philos[i].last_meal > conf->time_to_die)
			{
				pthread_mutex_unlock(conf->philos[i].meal_mutex);
				printf("%ld %d died\n", current_time
					- conf->philos[i].start_time, conf->philos[i].id);
				(pthread_mutex_lock(&conf->death_mutex), conf->died = 1);
				pthread_mutex_unlock(&conf->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(conf->philos[i].meal_mutex);
		}
		ft_sleep(1);
	}
	return (NULL);
}
