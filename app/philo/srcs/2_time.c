/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/30 11:36:35 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

/**
* Get current system time, since January, 1, 1970, 
* in miliseconds.
* @link ...
*/
long int	time_now(void)
{
	struct timeval	timeval;
	long int		time_now;
	long int		seconds_to_miliseconds;
	long int		microseconds_to_miliseconds;

	gettimeofday(&timeval, NULL);
	seconds_to_miliseconds = timeval.tv_sec * 1000;
	microseconds_to_miliseconds = timeval.tv_usec / 1000;
	time_now = seconds_to_miliseconds + microseconds_to_miliseconds;
	return (time_now);
}

/**
* Calculates how many 'miliseconds' has passed 
* from [start_time] until [time_now (the current
* system time)].
* @return difference between start_time and
* time_now in miliseconds.
*/
long int	get_time_passed_since(long int start_time)
{	
	return (time_now() - start_time);
}
