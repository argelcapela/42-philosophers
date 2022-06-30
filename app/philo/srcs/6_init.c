/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:47 by argel             #+#    #+#             */
/*   Updated: 2022/06/29 22:05:44 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

void	init_app(t_app *app, int argc, char **argv)
{
	app->n_philo = ft_atoi(argv[1]);
	app->time_to_die = ft_atoi(argv[2]);
	app->time_to_eat = ft_atoi(argv[3]);
	app->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		app->max_meals_by_philo = ft_atoi(argv[5]);
		app->max_meals = (app->max_meals_by_philo * app->n_philo);
	}
	else
	{
		app->max_meals_by_philo = -8;
		app->max_meals = -8;
	}
	if (!app->n_philo || !app->time_to_die || !app->max_meals_by_philo
		|| !app->time_to_eat || !app->time_to_sleep)
	{
		free(app);
		print(NULL, INVALID_ARGS);
	}
	app->stop = 0;
	app->start_time = get_time(0);
}

void	init_philos(t_philo **philo, t_app *app)
{
	int	i;

	i = 0;
	while (i < app->n_philo)
	{
		philo[0][i].app = app;
		philo[0][i].id = i;
		philo[0][i].meals = philo[0][i].app->max_meals_by_philo;
		pthread_create(&philo[0][i].thread, NULL, \
&routine, &philo[0][i]);
		philo[0][i].last_meal_time = get_time(0);
		i++;
	}
}
