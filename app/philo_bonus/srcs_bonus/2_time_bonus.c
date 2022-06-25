/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_time_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/25 15:26:11 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <0_philosophers_bonus.h>

/**
* As the function name says, it return the difference between
* current time in miliseconds and app->start_time (stored at 
* the beginning) also in miliseconds. It is used in each print
* of philo_circle_of_life creating allowing to print the exact
* miliseconds that each action was executed since the start of
* the application, always increasing until the app terminate.
*
*	- epoch: 1970, 00:00:00, Unix standard date.
*	- gettimeofday: get amount of microseconds from EPOCH until
*	your current time.
*	- timer.tv_sec: seconds
*	- timer.tv_usec: miliseconds
* @param timer struct that store the result from gettimeofday
* @param start_time generaly will be the app->start_time value
* which is the time application started, or zero, when this func-
* be called for the first time.
* @param current_time is literaly the current_time of the system
* @line 42 
* @line 43
*/
long int	get_time(long int last_meal_or_action_time)
{
	struct timeval	tv;
	long int		secon_to_mili;
	long int		micro_to_mili;
	long int		current_time;

	gettimeofday(&tv, NULL);
	secon_to_mili = tv.tv_sec * 1000;
	micro_to_mili = tv.tv_usec / 1000;
	current_time = secon_to_mili + micro_to_mili;
	if (last_meal_or_action_time != 0)
		current_time -= last_meal_or_action_time;
	return (current_time);
}

/**
* A function that execute the usleep but also
* works like a monitor, always check if some philosopher
* died, if so, finish app and print die message.
* @param
*/
void		msleep(long int time_to_wait, t_philosophers *philo)
{
	if (get_time(philo->last_meal_time) 
		> philo->app->time_to_die)
		{
			philo->app->stop = 1;	
			print(philo, DIE);
			exit_process(philo);
		}
	usleep(time_to_wait);	
}