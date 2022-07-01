/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/30 20:31:27 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

/**
* Get current system time, since January, 1, 1970, 
* in miliseconds.
* @link ...
*/
long	time_now(void)
{
	struct timeval	timeval;
	long			time_now;
	long			seconds_to_miliseconds;
	long			microseconds_to_miliseconds;

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

void	check_starvation(int i, t_philosophers **philo, t_app *app)
{
	long	tmp;

	pthread_mutex_lock(&app->lock_time);
	tmp = get_time_passed_since(philo[0][i].last_meal_time);
	pthread_mutex_unlock(&app->lock_time);
	if (tmp > app->time_to_die)
	{
		pthread_mutex_lock(&app->lock_app);
		app->stop = 1;
		pthread_mutex_unlock(&app->lock_app);
		usleep(500);
		print(&philo[0][i], DIE);
	}
	pthread_mutex_lock(&app->lock_meal);
}
