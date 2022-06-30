/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_init_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:50:48 by argel             #+#    #+#             */
/*   Updated: 2022/06/29 21:46:50 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

void	init_app(t_app *app, int argc, char **argv)
{
	sem_unlink("/forks");
	sem_unlink("/lock_print");
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
	app->start_time = 0;
	app->lock_print = sem_open("/lock_print", O_CREAT, 777, 1);
}

void	init_forks(t_philosophers **philo)
{
	(*philo)->app->forks = sem_open("/forks", O_CREAT, 0777,
			(*philo)->app->n_philo);
	if ((*philo)->app->forks == NULL)
		stop_routine((*philo), 1);
}

void	init_philosophers(t_philosophers **philo, t_app *app)
{
	int	i;

	i = 0;
	while (i < app->n_philo)
	{
		philo[0][i].app = app;
		philo[0][i].id = i;
		philo[0][i].name = i + 1;
		philo[0][i].meals = philo[0][i].app->max_meals_by_philo;
		philo[0][i].last_meal_time = 0;
		i++;
	}
}

void	start_routine(t_philosophers **philo)
{
	int	i;
	int	n_philo;

	n_philo = philo[0][0].app->n_philo;
	i = -1;
	philo[0][0].app->start_time = timestamp();
	while (++i < n_philo)
		create_process(&philo[0][i], &routine);
	wait_processes_finish(philo);
}
