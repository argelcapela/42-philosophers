/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_init_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:50:48 by argel             #+#    #+#             */
/*   Updated: 2022/07/01 15:11:23 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

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
		app->max_meals_by_philo = -616;
		app->max_meals = -616;
	}
	app->stop = 0;
	app->start_time = 0;
	if (parse_args(app) == 1)
		invalid_args();
	app->lock_print = sem_open("/lock_print", O_CREAT, 777, 1);
}

void	init_forks(t_philosophers **philo)
{
	(*philo)->app->forks = sem_open("/forks", O_CREAT, 0777,
			(*philo)->app->n_philo);
	if ((*philo)->app->forks == NULL)
		exit_process(philo, 1);
}

void	init_philosophers(t_philosophers **philo, t_app *app)
{
	int	i;

	i = 0;
	while (i < app->n_philo)
	{
		philo[0][i].app = app;
		philo[0][i].id = i;
		philo[0][i].right_fork = &app->forks;
		philo[0][i].left_fork = &app->forks;
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
	philo[0][0].app->start_time = time_now();
	while (++i < n_philo)
		create_process(&philo[0][i], &routine, philo);
	wait_processes_finish(philo);
}
