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

/*If times_must_eat (5th arg) was actually set, this
will checkc if all philos are satisfied. Returns 1 if
this is the case. 0 in all other cases (allowing monitor
to continue)*/
static int	all_philos_satisfied(t_config *conf)
{
	int	satisfied_count;
	int	i;

	if (conf->times_must_eat == -1)
		return (0);
	satisfied_count = 0;
	i = 0;
	while (i < conf->num_philos)
	{
		pthread_mutex_lock(conf->philos[i].meal_mutex);
		if (conf->philos[i].times_eaten >= conf->times_must_eat)
			satisfied_count++;
		pthread_mutex_unlock(conf->philos[i].meal_mutex);
		i++;
	}
	return (satisfied_count == conf->num_philos);
}

/*Cut from the original monitor
This is where the crux of what monitor calculates happens
Time since last meal being greater than time to die
This is a death case and will set the died flag*/
static int	helper(t_config *conf, int i)
{
	long	current_time;
	int		times_eaten;

	times_eaten = conf->philos[i].times_eaten;
	current_time = get_current_time();
	if (conf->times_must_eat > 0 && times_eaten >= conf->times_must_eat)
		return (pthread_mutex_unlock(conf->philos[i].meal_mutex), 0);
	if (current_time - conf->philos[i].last_meal > conf->time_to_die)
	{
		pthread_mutex_lock(&conf->death_mutex);
		conf->died = 1;
		pthread_mutex_unlock(&conf->death_mutex);
		pthread_mutex_unlock(conf->philos[i].meal_mutex);
		ft_print_die(&conf->philos[i]);
		return (1);
	}
	pthread_mutex_unlock(conf->philos[i].meal_mutex);
	return (0);
}

/*Check all philos satisfied (relevant where times_must_eat exists only).
 In the case where they are, diedflag will be set to 1 to end program
 rather than indicate a literal death case. Not satisfied or unlimited -1
 case simply moves onto helper where the original meat of monitor
 function takes place */
void	*monitor_routine(void *arg)
{
	t_config	*conf;
	int			i;

	conf = (t_config *)arg;
	while (1)
	{
		if (all_philos_satisfied(conf))
		{
			(pthread_mutex_lock(&conf->death_mutex), conf->died = 1);
			return (pthread_mutex_unlock(&conf->death_mutex), NULL);
		}
		i = -1;
		while (++i < conf->num_philos)
		{
			pthread_mutex_lock(conf->philos[i].meal_mutex);
			if (helper(conf, i) == 1)
				return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
