/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_time_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/29 21:49:25 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

/**
* Return the difference between current_time and some 'start_time'
* in miliseconds.
*
* @param 
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

long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	timenow(long firststamp)
{
	return (timestamp() - firststamp);
}

void	msleep(int time_in_ms)
{
	long	start_time;

	start_time = timestamp();
	while ((timestamp() - start_time) < (long)time_in_ms)
		usleep(10);
}

void	dsleep(int time_in_ms, t_philosophers *philo)
{
	long	current_time;
	long	start_time;

	start_time = timestamp();
	while ((timestamp() - start_time) < (long)time_in_ms)
	{
		usleep(10);
		current_time = timenow(philo->app->start_time);
		if ((current_time - philo->last_meal_time) > philo->app->time_to_die)
		{
			print(philo, DIE);
			stop_routine(philo, 1);
		}
	}
}

// /**
// * A function that execute the usleep but also
// * works like a monitor, always check if some philosopher
// * died, if so, finish app and print die message.
// *
// * @param
// */
// void	msleep(int time_to_wait, t_philosopherssophers *philo)
// {
// 	while (time_to_wait)
// 	{	
// 		if (get_time(0) > philo->limit)
// 		{
// 			print(philo, DIE);
// 			stop_routine(philo, 1);
// 		}
// 		usleep(10);
// 		time_to_wait -= 10;
// 	}
// }
