/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecicle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:24:49 by aprotoce          #+#    #+#             */
/*   Updated: 2022/04/10 21:24:49 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_think(t_philo *philo, int time)
{
	if (philo->env->stop)
		return ;
	print(philo, THINK);
	if (time)
		usleep(time);
}

static void	philo_sleep(t_philo *philo)
{
	if (philo->env->stop)
		return ;
	print(philo, SLEEP);
	usleep(philo->env->time_to_sleep * 1000);
}

static int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->fork[philo->id]);
	print(philo, FORK);
	if (philo->env->stop)
	{
		pthread_mutex_unlock(&philo->env->fork[philo->id]);
		return (1);
	}
	if (philo->env->n_philos == 1)
		return (1);
	else if (philo->id == philo->env->n_philos - 1)
		pthread_mutex_lock(&philo->env->fork[0]);
	else
		pthread_mutex_lock(&philo->env->fork[philo->id + 1]);
	print(philo, FORK);
	print(philo, EAT);
	philo->last_meal = get_time(0);
	usleep(philo->env->time_to_eat * 1000);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->env->fork[philo->id]);
	if (philo->id == philo->env->n_philos - 1)
		pthread_mutex_unlock(&philo->env->fork[0]);
	else
		pthread_mutex_unlock(&philo->env->fork[philo->id + 1]);
	return (0);
}

void	*lifecicle(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2)
		philo_think(philo, philo->env->time_to_eat);
	while (!philo->env->stop)
	{
		if (philo_eat(philo) || philo->env->stop)
			break ;
		philo_sleep(philo);
		philo_think(philo, 0);
	}
	return (NULL);
}
