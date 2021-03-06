/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:47 by argel             #+#    #+#             */
/*   Updated: 2022/07/01 15:12:27 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

static int	parse_args(t_app *app)
{
	if (!app->n_philo
		|| !app->time_to_die
		|| !app->time_to_eat
		|| !app->time_to_sleep
		|| (app->n_philo > 200)
		|| (app->n_philo <= 0)
		|| (app->time_to_die < 60)
		|| (app->time_to_eat < 60)
		|| (app->time_to_sleep < 60))
		return (1);
	if (!app->max_meals_by_philo
		|| (app->max_meals_by_philo != -616
			&& app->max_meals_by_philo <= 0))
		return (1);
	return (0);
}

void	init_app(t_app *app, int argc, char **argv)
{
	app->n_philo = ft_atoi(argv[1]);
	app->time_to_die = ft_atoi(argv[2]);
	app->time_to_eat = ft_atoi(argv[3]);
	app->time_to_sleep = ft_atoi(argv[4]);
	app->start_time = 0;
	app->stop = 0;
	if (argc == 6)
	{
		app->max_meals_by_philo = ft_atoi(argv[5]);
		app->max_meals = (app->max_meals_by_philo * app->n_philo);
	}
	else
	{
		app->max_meals_by_philo = -616;
		app->max_meals = -616;
	}
	if (parse_args(app) == 1)
		invalid_args();
}

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
	pthread_mutex_init(&app->lock_meal, NULL);
	pthread_mutex_init(&app->lock_print, NULL);
	pthread_mutex_init(&app->lock_time, NULL);
	pthread_mutex_init(&app->lock_app, NULL);
	pthread_mutex_init(&app->lock_any, NULL);
}

void	init_philosophers(t_philosophers **philo, t_app *app)
{
	int	i;

	i = 0;
	app->start_time = time_now();
	while (i < app->n_philo)
	{
		philo[0][i].app = app;
		philo[0][i].id = i;
		philo[0][i].right_fork = &app->fork[i];
		if (i == 0)
			philo[0][i].left_fork = &app->fork[(app->n_philo - 1)];
		else
			philo[0][i].left_fork = &app->fork[i - 1];
		philo[0][i].meals = philo[0][i].app->max_meals_by_philo;
		philo[0][i].last_meal_time = time_now();
		pthread_create(&philo[0][i].thread, NULL, \
&routine, &philo[0][i]);
		i++;
	}
}
