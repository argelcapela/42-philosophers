/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_time_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/28 21:43:45 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>
#include <stdint.h>

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

/**
* A function that execute the usleep but also
* works like a monitor, always check if some philosopher
* died, if so, finish app and print die message.
*
* @param
*/
void	msleep(long int time_to_wait, t_philosophers *philo)
{
	long int die_time;

	if (philo->app->n_philo == 1)
	{
		print(philo, DIE);
		stop_routine(philo, 1);
	}
	while (time_to_wait > 0)
	{
		time_to_wait -= 10;
		usleep(10);
		die_time = get_time(philo->last_meal_time) - 1;
		if (die_time > philo->app->time_to_die)
		{
			print(philo, DIE);
			stop_routine(philo, 1);
		}
	}
}
