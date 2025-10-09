/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:02:30 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/07 17:02:41 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->conf->death_mutex);
	dead = philo->conf->died;
	pthread_mutex_unlock(&philo->conf->death_mutex);
	return (dead);
}

static void	take_or_leave_fork(t_philo *philo, int on)
{
	if (on)
	{
		if (philo->id == philo->conf->num_philos)
			(pthread_mutex_lock(philo->right_fork),
				pthread_mutex_lock(philo->left_fork));
		else
			(pthread_mutex_lock(philo->left_fork),
				pthread_mutex_lock(philo->right_fork));
	}
	else
	{
		if (philo->id == philo->conf->num_philos)
			(pthread_mutex_unlock(philo->right_fork),
				pthread_mutex_unlock(philo->left_fork));
		else
			(pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork));
	}
}

/*This function is merely a helper that was taken out of
philo_routine. The cutoff phase was chose more because it
coult take a single parameter directly after the first use
of "death". It might be more aesthetic if it were more
focused. This is virtually unchanged from the original sequence
because it was easily done with a pointer to the philo struct
to appease Norminette*/
static void	end_phase(t_philo *philo)
{
	if (check_death(philo))
		return ;
	take_or_leave_fork(philo, 1);
	if (check_death(philo))
	{
		take_or_leave_fork(philo, 0);
		return ;
	}
	printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time,
		philo->id);
	printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time,
		philo->id);
	printf("%ld %d is eating\n", get_current_time() - philo->start_time,
		philo->id);
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_mutex);
	ft_sleep(philo->conf->time_to_eat);
	take_or_leave_fork(philo, 0);
	if (check_death(philo))
		return ;
	printf("%ld %d is sleeping\n", get_current_time() - philo->start_time,
		philo->id);
	ft_sleep(philo->conf->time_to_sleep);
}

void	*looper(t_philo *philo)
{
	int	dead;

	while (1)
	{
		pthread_mutex_lock(&philo->conf->death_mutex);
		dead = philo->conf->died;
		pthread_mutex_unlock(&philo->conf->death_mutex);
		if (dead)
		{
			return (NULL);
		}
		printf("%ld %d is thinking\n", get_current_time() - philo->start_time,
			philo->id);
		ft_sleep(1);
		pthread_mutex_lock(&philo->conf->death_mutex);
		dead = philo->conf->died;
		if (dead)
		{
			return (NULL);
		}
		pthread_mutex_unlock(&philo->conf->death_mutex);
		end_phase(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (check_death(philo))
		return (NULL);
	if (philo->conf->num_philos == 1)
	{
		printf("%ld %d has taken a fork\n", get_current_time()
			- philo->start_time, philo->id);
		ft_sleep(philo->conf->time_to_die);
		printf("%ld %d died\n", get_current_time() - philo->start_time,
			philo->id);
		pthread_mutex_lock(&philo->conf->death_mutex);
		philo->conf->died = 1;
		pthread_mutex_unlock(&philo->conf->death_mutex);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_sleep(philo->conf->time_to_eat / 2);
	return (looper(philo));
	return (NULL);
}
