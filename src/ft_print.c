/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:01:58 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/09 19:02:05 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

void	ft_print_eat(t_philo *philo)
{
	ft_print(philo, "is eating");
}

void	ft_print_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
}

void	ft_print_fork(t_philo *philo)
{
	ft_print(philo, "has taken a fork");
}

/*This is the one print here containing a mutex lock
of its own because it is ALWAYS called directly rather
than through the standard ft_print. The core complication
is that death must always print and ft_print is designed
to preven printing after death flag is triggered*/
void	ft_print_die(t_philo *philo)
{
	long	timestamp;

	timestamp = get_current_time() - philo->start_time;
	pthread_mutex_lock(&philo->conf->print_mutex);
	printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->conf->print_mutex);
}
