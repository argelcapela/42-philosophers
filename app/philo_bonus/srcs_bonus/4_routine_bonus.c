/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_routine_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/29 21:48:43 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

static int	go_eat(t_philosophers *philo)
{
	sem_wait(philo->app->forks);
	sem_wait(philo->app->forks);
	print(philo, FORK);
	print(philo, FORK);
	print(philo, EAT);
	philo->last_meal_time = timenow(philo->app->start_time);
	dsleep(philo->app->time_to_eat, philo);
	sem_post(philo->app->forks);
	sem_post(philo->app->forks);
	philo->meals--;
	philo->app->max_meals--;
	return (0);
}

static int	go_sleep(t_philosophers *philo)
{
	print(philo, SLEEP);
	dsleep(philo->app->time_to_sleep, philo);
	return (0);
}

void	sem_try_wait(t_philosophers *philo)
{
	long	current_time;

	while (*(long *)philo->app->forks < 2)
	{
		current_time = timenow(philo->app->start_time);
		if ((current_time - philo->last_meal_time) > philo->app->time_to_die)
		{
			print(philo, DIE);
			stop_routine(philo, 1);
		}
		usleep(10);
	}
}

static int	go_think(t_philosophers *philo)
{
	print(philo, THINK);
	usleep(500);
	sem_try_wait(philo);
	return (0);
}

int	routine(t_philosophers **p_philo)
{	
	t_philosophers	*philo;

	philo = *p_philo;
	if (philo->name % 2 == 0)
		msleep(5);
	if (philo->app->n_philo == 1)
	{
		print(philo, DIE);
		stop_routine(philo, 1);
	}
	while (1)
	{
		go_eat(philo);
		if (philo->meals == 0)
			stop_routine(philo, 0);
		go_sleep(philo);
		go_think(philo);
	}
	return (0);
}
