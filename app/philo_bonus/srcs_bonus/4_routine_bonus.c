/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_routine_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/25 15:25:09 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <0_philosophers_bonus.h>

static int	go_eat(t_philosophers *philo)
{
	if (philo->app->stop)
		exit_process(0);
	// pthread_mutex_lock(&philo->app->fork[philo->id]);
	// if (philo->app->stop)
	// {
	// 	pthread_mutex_unlock(&philo->app->fork[philo->id]);
	// 	return (1);
	// }
	print(philo, FORK);
	// if (philo->app->n_philo == 1)
	// 	return (1);
	// else if (philo->id == (philo->app->n_philo - 1))
	// 	pthread_mutex_lock(&philo->app->fork[0]);
	// else
	// 	pthread_mutex_lock(&philo->app->fork[philo->id + 1]);
	print(philo, FORK);
	print(philo, EAT);
	philo->last_meal_time = get_time(0);
	msleep(philo->app->time_to_eat * 1000, philo);
	philo->meals--;
	philo->app->max_meals--;
	// pthread_mutex_unlock(&philo->app->fork[philo->id]);
	// if (philo->id == (philo->app->n_philo - 1))
	// 	pthread_mutex_unlock(&philo->app->fork[0]);
	// else
	// 	pthread_mutex_unlock(&philo->app->fork[philo->id + 1]);
	return (0);
}

static int	go_sleep(t_philosophers *philo)
{
	if (philo->app->stop)
		exit_process(0);
	print(philo, SLEEP);
	msleep(philo->app->time_to_sleep * 1000, philo);
	return (0);
}

static int	go_think(t_philosophers *philo, int time)
{
	if (philo->app->stop)
		exit_process(0);
	print(philo, THINK);
	if (time != 0)
		msleep(time, philo);
	return (0);
}

void	routine(void *p_philo)
{
	t_philosophers	*philo;
	int		time_to_think;

	philo = p_philo;
	time_to_think = philo->app->time_to_eat;
	if ((philo->id % 2) != 0)
		go_think(philo, time_to_think);
	while (!philo->app->stop)
	{
		if(philo->meals == 0
		|| go_eat(philo)
		|| go_sleep(philo)
		|| go_think(philo, 0)
		|| philo->app->stop)
				exit_process(0);
	}
}
