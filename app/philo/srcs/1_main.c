/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/28 22:01:02 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

void	inspector(t_philo **philo, t_app *app)
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
		//pthread_mutex_lock(philo[0][i].app->lock_time);
		if (get_time(philo[0][i].last_meal_time) > app->time_to_die)
		{
			app->stop = 1;
			usleep(500);
			print(&philo[0][i], DIE);
		}
		//pthread_mutex_unlock(philo[0][i].app->lock_time);
		if (app->max_meals == 0)
			app->stop = 1;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_app	app;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		print(NULL, INVALID_ARGS);
	init_app(&app, argc, argv);
	philo = malloc(app.n_philo * sizeof(t_philo));
	init_forks(&app);
	init_philos(&philo, &app);
	inspector(&philo, &app);
	ensure_threads_terminate(&philo);
	destroy_forks(&app);
	free(app.fork);
	free(philo);
	return (0);
}
