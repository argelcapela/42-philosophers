/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_threads_mutexes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:30 by argel             #+#    #+#             */
/*   Updated: 2022/06/29 21:58:32 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

void	init_forks(t_app *app)
{
	int	i;

	app->fork = malloc(app->n_philo * \
sizeof(pthread_mutex_t));
	i = 0;
	while (i < app->n_philo)
	{
		pthread_mutex_init(&app->fork[i], NULL);
		i++;
	}
}

void	destroy_forks(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->n_philo)
	{
		pthread_mutex_destroy(&app->fork[i]);
		i++;
	}
}

void	ensure_threads_terminate(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*philo)->app->n_philo)
	{
		pthread_join(philo[0][i].thread, NULL);
		i++;
	}
}
