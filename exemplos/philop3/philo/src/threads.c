/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:25:30 by aprotoce          #+#    #+#             */
/*   Updated: 2022/04/10 21:25:30 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutex(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->n_philos)
	{
		pthread_mutex_init(&env->fork[i], NULL);
		i++;
	}
}

void	join_threads(t_philo **philo, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->n_philos)
	{
		pthread_join(philo[0][i].thread, NULL);
		i++;
	}
}

void	destroy_mutex(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->n_philos)
	{
		pthread_mutex_destroy(&env->fork[i]);
		i++;
	}
}
