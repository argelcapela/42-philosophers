/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/30 20:35:54 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

static int	go_eat_lock(t_philosophers *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print(philo, FORK);
	pthread_mutex_lock(&philo->app->lock_app);
	if (philo->app->stop)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->app->lock_app);
		return (1);
	}
	pthread_mutex_unlock(&philo->app->lock_app);
	if (philo->app->n_philo == 1)
		return (1);
	else
		pthread_mutex_lock(philo->left_fork);
	return (0);
}

static int	go_eat(t_philosophers *philo)
{
	if (go_eat_lock(philo))
		return (1);
	print(philo, FORK);
	print(philo, EAT);
	pthread_mutex_lock(&philo->app->lock_time);
	philo->last_meal_time = get_time_passed_since(0);
	pthread_mutex_unlock(&philo->app->lock_time);
	usleep(philo->app->time_to_eat * 1000);
	pthread_mutex_lock(&philo->app->lock_meal);
	philo->meals--;
	philo->app->max_meals--;
	pthread_mutex_unlock(&philo->app->lock_meal);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

static int	go_sleep(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->app->lock_app);
	if (philo->app->stop)
	{
		pthread_mutex_unlock(&philo->app->lock_app);
		return (1);
	}
	pthread_mutex_unlock(&philo->app->lock_app);
	print(philo, SLEEP);
	usleep(philo->app->time_to_sleep * 1000);
	return (0);
}

static int	go_think(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->app->lock_app);
	if (philo->app->stop)
	{
		pthread_mutex_unlock(&philo->app->lock_app);
		return (1);
	}
	pthread_mutex_unlock(&philo->app->lock_app);
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
	while (1)
	{
		pthread_mutex_lock(&philo->app->lock_app);
		if (philo->app->stop)
		{
			pthread_mutex_unlock(&philo->app->lock_app);
			break ;
		}
		pthread_mutex_unlock(&philo->app->lock_app);
		if (philo->meals == 0
			|| go_eat(philo)
			|| go_sleep(philo)
			|| go_think(philo))
			break ;
	}
	return (NULL);
}
