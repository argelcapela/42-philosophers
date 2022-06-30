/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/30 10:42:08 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

static int	go_eat(t_philosophers *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (philo->app->n_philo == 1)
		return (1);
	pthread_mutex_lock(philo->left_fork);
	print(philo, FORK);
	print(philo, FORK);
	print(philo, EAT);
	philo->last_meal_time = get_time_passed_since(0);
	usleep(philo->app->time_to_eat * 1000);
	philo->meals--;
	philo->app->max_meals--;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

static int	go_sleep(t_philosophers *philo)
{
	if (philo->app->stop)
		return (1);
	print(philo, SLEEP);
	usleep(philo->app->time_to_sleep * 1000);
	return (0);
}

static int	go_think(t_philosophers *philo)
{
	if (philo->app->stop)
		return (1);
	print(philo, THINK);
	usleep(500);
	return (0);
}

void	*routine(void *p_philo)
{
	t_philosophers	*philo;

	philo = p_philo;
	if (philo->id % 2)
		usleep(5 * 1000);
	while (!philo->app->stop)
	{
		if (philo->meals == 0
			|| go_eat(philo)
			|| go_sleep(philo)
			|| go_think(philo)
			|| philo->app->stop)
			break ;
	}
	return (NULL);
}
