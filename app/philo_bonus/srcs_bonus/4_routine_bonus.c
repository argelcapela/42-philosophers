/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_routine_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/28 21:46:13 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

static int	go_eat(t_philosophers *philo)
{
	print(philo, FORK);
	sem_wait(philo->app->forks);
	sem_wait(philo->app->forks);
	print(philo, FORK);
	print(philo, EAT);
	philo->last_meal_time = get_time(0);
	usleep(philo->app->time_to_eat * 1000);
	philo->meals--;
	philo->app->max_meals--;
	sem_post(philo->app->forks);
	sem_post(philo->app->forks);
	return (0);
}

static int	go_sleep(t_philosophers *philo)
{
	print(philo, SLEEP);
	msleep(philo->app->time_to_sleep * 1000, philo);
	return (0);
}

static int	go_think(t_philosophers *philo, int time)
{
	print(philo, THINK);
	if (time != 0)
		usleep(time);
	return (0);
}

int	routine(t_philosophers **p_philo)
{	
	t_philosophers	*philo;
	int				time_to_think;

	philo = *p_philo;
	time_to_think = philo->app->time_to_eat;
	if (philo->id % 2)
		go_think(philo, time_to_think);
	msleep(10 ,philo);
	while (1)
	{
		if (philo->meals == 0)
			stop_routine(philo, 0);
		go_eat(philo);
		go_sleep(philo);
		go_think(philo, 0);
	}
	return (0);
}
