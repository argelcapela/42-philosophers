/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_monitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:54 by argel             #+#    #+#             */
/*   Updated: 2022/06/30 20:31:48 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

void	monitor(t_philosophers **philo, t_app *app)
{
	int		i;

	i = 0;
	while (!app->stop)
	{
		if (i == (app->n_philo))
		{
			usleep(50);
			i = 0;
		}
		check_starvation(i, philo, app);
		if (app->max_meals == 0)
		{
			pthread_mutex_lock(&app->lock_app);
			app->stop = 1;
			pthread_mutex_unlock(&app->lock_app);
		}
		i++;
		pthread_mutex_unlock(&app->lock_meal);
	}
}
