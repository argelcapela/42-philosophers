/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/22 17:41:46 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	philo_eat(t_philo *philo)
{
	if (philo->app->stop == 0)
		pthread_mutex_unlock(&philo->app->died);
	else
		return (1);
	pthread_mutex_lock(&philo->app->fork[philo->id]);
	print(philo, FORK);
	if (philo->app->n_philo == 1)
		return (1);
	if (philo->id == philo->app->n_philo - 1)
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
	if (philo->id == philo->app->n_philo - 1)
		pthread_mutex_unlock(&philo->app->fork[0]);
	else
		pthread_mutex_unlock(&philo->app->fork[philo->id + 1]);
	return (0);
}

static void	philo_sleep(t_philo *philo)
{
	if (philo->app->stop == 1)
		return ;
	print(philo, SLEEP);
	usleep(philo->app->time_to_sleep * 1000);
}

static void	philo_think(t_philo *philo, int time)
{
	if (philo->app->stop == 1)
		return ;
	print(philo, THINK);
	if (time != 0)
		usleep(time);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *) p_philo;
	if (philo->app->stop)
			pthread_mutex_lock(&philo->app->died);
	if ((philo->id % 2))
		philo_think(philo, philo->app->time_to_eat);
	while (philo->app->stop == 0)
	{
		pthread_mutex_lock(&philo->app->died);
		if (philo_eat(philo) ||philo->meals == 0 || philo->app->stop == 1)
			break ;
		philo_sleep(philo);
		philo_think(philo, 0);
	}
	return (NULL);
}
