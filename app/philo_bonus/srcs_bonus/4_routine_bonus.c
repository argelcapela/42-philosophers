/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_routine_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/07/01 08:49:00 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

static int	just_one_go_eat(t_philosophers *philo)
{
	if (philo->app->n_philo == 1)
	{
		usleep(1000 * philo->app->time_to_die);
		print(philo, DIE);
		exit_process(&philo, 1);
		return (1);
	}
	return (0);
}

static int	go_eat(t_philosophers *philo)
{
	sem_wait(*philo->right_fork);
	print(philo, FORK);
	sem_wait(*philo->left_fork);
	print(philo, FORK);
	print(philo, EAT);
	philo->last_meal_time = get_time_passed_since(philo->app->start_time);
	if (msleep(philo->app->time_to_eat, philo))
	{
		sem_post(*philo->right_fork);
		sem_post(*philo->left_fork);
		return (1);
	}
	philo->meals--;
	philo->app->max_meals--;
	sem_post(*philo->right_fork);
	sem_post(*philo->left_fork);
	return (0);
}

static int	go_sleep(t_philosophers *philo)
{
	print(philo, SLEEP);
	if (msleep(philo->app->time_to_sleep, philo))
		return (1);
	return (0);
}

static int	go_think(t_philosophers *philo)
{
	print(philo, THINK);
	usleep(500);
	while (*(long *)philo->app->forks < 2)
	{
		if (check_starvation(philo))
			return (1);
		usleep(10);
	}
	return (0);
}

int	routine(t_philosophers *philo)
{	
	if (philo->id % 2)
		usleep(5 * 1000);
	just_one_go_eat(philo);
	while (1)
	{
		if (philo->meals == 0
			|| go_eat(philo)
			|| go_sleep(philo)
			|| go_think(philo))
			return (1);
	}
	return (0);
}
