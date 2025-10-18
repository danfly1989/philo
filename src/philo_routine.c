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

/*Literally just checks the death flag on a philo
Only needs to be a function because of the overmutexing
that is the entire source of difficulty in this project.
and Norminette of course*/
int	check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->conf->death_mutex);
	dead = philo->conf->died;
	pthread_mutex_unlock(&philo->conf->death_mutex);
	return (dead);
}

/*Uses input flag int for true or false. If set to true
(1), fork is picked up. Released if 0 or other. Even philo
picks up right fork first, releases right fork first. Odd philo
is exactly the converse.*/
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
philo_routine. The cutoff phase was chosen more because it
coult take a single parameter directly after the first use
of "death". It might be more aesthetic if it were more
focused. This is virtually unchanged from the original sequence
because it was easily done with a pointer to the philo struct
to appease Norminette*/
static void	end_phase(t_philo *philo)
{
	// int	full;
	if (check_death(philo))
		return ;
	take_or_leave_fork(philo, 1);
	if (check_death(philo))
		return (take_or_leave_fork(philo, 0), (void)0);
	(ft_print_fork(philo), ft_print_fork(philo), ft_print_eat(philo));
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_current_time();
	philo->times_eaten++;
	// full = (philo->conf->times_must_eat > 0
	//		&& philo->times_eaten >= philo->conf->times_must_eat);
	pthread_mutex_unlock(philo->meal_mutex);
	ft_sleep(philo->conf->time_to_eat);
	// if (full)
	//	return (take_or_leave_fork(philo, 0), (void)0);
	take_or_leave_fork(philo, 0);
	if (check_death(philo))
		return ;
	ft_print_sleep(philo);
	ft_sleep(philo->conf->time_to_sleep);
}

/*Run continuous death check on whose routine we are running. Print think
(no calc necessary), check death again, run end phase if no death found,
which is in turn another extracted function, allowing usual routine to continue.
Check if full after eating to exit when quota is met.
Returns NULL on death or full satisfaction (exhausts all possibilities - loop
will always hit one of these terminal conditions)*/
void	*looper(t_philo *philo)
{
	// int	full;
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		ft_print_think(philo);
		if (check_death(philo))
			return (NULL);
		end_phase(philo);
		// pthread_mutex_lock(philo->meal_mutex);
		// full = (philo->conf->times_must_eat > 0
		// 		&& philo->times_eaten >= philo->conf->times_must_eat);
		// pthread_mutex_unlock(philo->meal_mutex);
		// if (full)
		// {
		// 	return (NULL);
		// }
	}
}

/*Check for death and deal with the philo 1 case
If multiple philosophers exist, stagger start time
for even philos and go to the core logic in looper
(originally an extracted function). Although Looper
will always return NULL because void* type, it is
required by philo_routine syntax, which was in turn
dictated by pthread_create requirements*/
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
