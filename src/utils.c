/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_positive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:50:51 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/06 11:18:41 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*A general print function that keeps track of time relative
to given philosopher start time and prints the input message
at approptiate timestamp. This is virtually always called by
one of the print functions in ft_print.c, which will define the
appropriate message; think, eat etc. It ensures each of these
basic print functions is adequalely mutexed*/
void	ft_print(t_philo *philo, char *message)
{
	long	timestamp;

	timestamp = get_current_time() - philo->start_time;
	pthread_mutex_lock(&philo->conf->print_mutex);
	if (!check_death(philo))
		printf("%ld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->conf->print_mutex);
}

/*Atoi function designed to ensure only valid (positive input)
and return -1 when invalid, or return the actual converted number
on success*/
int	ft_atoi_positive(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] == '+' || str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (result <= 0 || str[i] != '\0')
		return (-1);
	else
		return (result);
}

/*Destroy all mutex locks and free
all global conf variables that were
malloced at the start*/
void	ft_destroy(t_config *conf)
{
	int	i;

	i = -1;
	while (++i < conf->num_philos)
		pthread_mutex_destroy(&conf->meal_mutexes[i]);
	pthread_mutex_destroy(&conf->death_mutex);
	pthread_mutex_destroy(&conf->print_mutex);
	free(conf->forks);
	free(conf->threads);
	free(conf->philos);
	free(conf->meal_mutexes);
}
