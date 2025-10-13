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

int	check_death(t_philo *philo)
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
		if (philo->id % 2 == 0)
			(pthread_mutex_lock(philo->right_fork),
				pthread_mutex_lock(philo->left_fork));
		else
			(pthread_mutex_lock(philo->left_fork),
				pthread_mutex_lock(philo->right_fork));
	}
	else
	{
		if (philo->id % 2 == 0)
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
	int	full;

	if (check_death(philo))
		return ;
	take_or_leave_fork(philo, 1);
	if (check_death(philo))
	{
		take_or_leave_fork(philo, 0);
		return ;
	}
	(ft_print_fork(philo), ft_print_fork(philo), ft_print_eat(philo));
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_current_time();
	philo->times_eaten++;
	ft_sleep(philo->time_to_eat);
	full = (philo->conf->times_must_eat > 0
			&& philo->times_eaten >= philo->conf->times_must_eat);
	pthread_mutex_unlock(philo->meal_mutex);
	if (full)
	{
		take_or_leave_fork(philo, 0);
		return ;
	}
	ft_sleep(philo->conf->time_to_eat);
	take_or_leave_fork(philo, 0);
	if (check_death(philo))
		return ;
	ft_print_sleep(philo);
	ft_sleep(philo->conf->time_to_sleep);
}

void	*looper(t_philo *philo)
{
	int	full;

	while (1)
	{
		if (check_death(philo))
			return (NULL);
		ft_print_think(philo);
		// ft_sleep(philo->conf->time_to_eat / 2);
		if (check_death(philo))
			return (NULL);
		end_phase(philo);
		pthread_mutex_lock(philo->meal_mutex);
		full = (philo->conf->times_must_eat > 0
				&& philo->times_eaten >= philo->conf->times_must_eat);
		pthread_mutex_unlock(philo->meal_mutex);
		if (full)
		{
			return (NULL);
		}
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
		ft_print_fork(philo);
		ft_sleep(philo->conf->time_to_die);
		pthread_mutex_lock(&philo->conf->death_mutex);
		philo->conf->died = 1;
		pthread_mutex_unlock(&philo->conf->death_mutex);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_sleep(philo->conf->time_to_eat / 2);
	return (looper(philo));
}
