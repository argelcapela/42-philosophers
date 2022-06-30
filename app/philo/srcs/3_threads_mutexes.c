/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_threads_mutexes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:30 by argel             #+#    #+#             */
/*   Updated: 2022/06/30 09:53:06 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

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

void	wait_threads_exit(t_philosophers **philo)
{
	int	i;

	i = 0;
	while (i < (*philo)->app->n_philo)
	{
		pthread_join(philo[0][i].thread, NULL);
		i++;
	}
}
