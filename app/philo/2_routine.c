/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/23 16:58:55 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->app->fork[philo->id]);
	if (philo->app->stop)
	{
		pthread_mutex_unlock(&philo->app->fork[philo->id]);
		return (1);
	}
	print(philo, FORK);
	if (philo->app->n_philo == 1)
		return (1);
	else if (philo->id == (philo->app->n_philo - 1))
		pthread_mutex_lock(&philo->app->fork[0]);
	else
		pthread_mutex_lock(&philo->app->fork[philo->id + 1]);
	print(philo, FORK);
	print(philo, EAT);
	philo->last_meal_time = get_time(0);
	usleep(philo->app->time_to_eat * 1000);
	philo->meals--;
	philo->app->max_meals--;
	pthread_mutex_unlock(&philo->app->fork[philo->id]);
	if (philo->id == (philo->app->n_philo - 1))
		pthread_mutex_unlock(&philo->app->fork[0]);
	else
		pthread_mutex_unlock(&philo->app->fork[philo->id + 1]);
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	if (philo->app->stop)
		return (1);
	print(philo, SLEEP);
	usleep(philo->app->time_to_sleep * 1000);
	return (0);
}

static int	philo_think(t_philo *philo, int time)
{
	if (philo->app->stop)
		return (1);
	print(philo, THINK);
	if (time != 0)
		usleep(time);
	return (0);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;
	int		time_to_think;

	philo = p_philo;
	time_to_think = philo->app->time_to_eat;
	if ((philo->id % 2) != 0)
		philo_think(philo, time_to_think);
	while (!philo->app->stop)
	{
		if (philo->meals == 0 ||
			philo_eat(philo) || 
			philo_sleep(philo) ||  
			philo_think(philo, 0) ||
			philo->app->stop)
			break ;
	}
	return (NULL);
}
