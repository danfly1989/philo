/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:57:35 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/07 16:57:42 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Uses the timeval struct defined in sys/time.h to get
current time through the gettimeofday function. Returns time in milliseceons
calculated by total seconds since unix epoch tv_sec * 1000 for ms value, added
to fractional microseconds within that second converted to ms through division
by 1000. This is used for start time initialization and the print function calcs
it against time past to get accurate timestamps printed to the terminal. */
long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(long milliseconds)
{
	long	start;
	long	target;

	start = get_current_time();
	target = start + milliseconds;
	while (get_current_time() < target)
		usleep(500);
}
