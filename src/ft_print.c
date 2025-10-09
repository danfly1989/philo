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

void	ft_print_die(t_philo *philo)
{
	ft_print(philo, "died");
}
