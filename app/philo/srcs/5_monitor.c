/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_monitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:54 by argel             #+#    #+#             */
/*   Updated: 2022/06/30 09:53:20 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

void	monitor(t_philosophers **philo, t_app *app)
{
	int	i;

	i = 0;
	while (!app->stop)
	{
		if (i == (app->n_philo))
		{
			usleep(50);
			i = 0;
		}
		if (get_time_passed_since(philo[0][i].last_meal_time)
		> app->time_to_die)
		{
			app->stop = 1;
			usleep(500);
			print(&philo[0][i], DIE);
		}
		if (app->max_meals == 0)
			app->stop = 1;
		i++;
	}
}
