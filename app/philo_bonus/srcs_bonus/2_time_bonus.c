/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_time_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/30 20:55:10 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

/**
* Get current system time, since January, 1, 1970, 
* in miliseconds.
* @link ...
*/
long	time_now(void)
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
long	get_time_passed_since(long start_time)
{	
	return (time_now() - start_time);
}

void	check_starvation(t_philosophers *philo)
{
	long	curr_time_since_start_time;
	long	time_since_last_meal;

	curr_time_since_start_time = \
		get_time_passed_since(philo->app->start_time);
	time_since_last_meal = \
		(curr_time_since_start_time - philo->last_meal_time);
	if (time_since_last_meal > philo->app->time_to_die)
	{
		print(philo, DIE);
		exit_process(&philo, 1);
	}
}

/**
* Stop the process during [long time_to_wait] microseconds.
* Each 10 microseconds is checked is some philo died.
* @param time_to_wait in microseconds or x (miliseconds) * 1000
* @param philo pointer to variable holding philosophers
* @line 59-60:Get time that msleep was executed and holds in start_time;
* Loop executes, usleeping 10 in 10, while start_time was not
* achieved yet;
*/
void	msleep(long time_to_wait, t_philosophers *philo)
{
	long	start_time;

	start_time = time_now();
	while (get_time_passed_since(start_time) < time_to_wait)
	{
		usleep(10);
		check_starvation(philo);
	}
}
