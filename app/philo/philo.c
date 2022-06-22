/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/22 09:29:23 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	parse_args(int argc, char **argv);
void	init_app(t_app *app, int argc, char **argv);
void	init_philos(t_philo **philos, t_app *app);
void	inspector(t_philo **philo, t_app *app);

int	main(int argc, char **argv)
{
	t_app	app;
	t_philo	*philo;

	philo = NULL;
	if (argc < 5 || argc > 6)
		print(NULL, INVALID_ARGS);
	init_app(&app, argc, argv);
	init_forks(&app);
	init_philos(&philo, &app);
	inspector(&philo, &app);
	ensure_threads_terminate(&philo, &app);
	destroy_forks(&app);
	free(philo);
	free(app.fork);
	return (0);
}

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
	app->stop = 0;
	app->start_time = get_time(0);
}

void	init_philos(t_philo **philo, t_app *app)
{
	int	i;

	(*philo) = malloc(app->n_philo * sizeof(t_philo));
	i = 0;
	while (i < app->n_philo)
	{
		philo[0][i].app = app;
		philo[0][i].id = i;
		philo[0][i].last_meal_time = get_time(0);
		philo[0][i].meals = philo[0][i].app->max_meals_by_philo;
		pthread_create(&philo[0][i].thread, NULL, \
&philo_circle_of_life, &philo[0][i]);
		i++;
	}
}

void	inspector(t_philo **philo, t_app *app)
{
	int	i;

	i = 0;
	while (app->stop == 0)
	{
		if (i == app->n_philo)
		{
			usleep(50);
			i = 0;
		}	
		if (get_time(philo[0][i].last_meal_time) > app->time_to_die)
		{
			app->stop = 1;
			print(&philo[0][i], DIE);
			free(*philo);
			free(app->fork);
			exit(0);
		}
		if (app->max_meals == 0)
			app->stop = 1;
		i++;
	}
}
