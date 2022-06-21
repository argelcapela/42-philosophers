/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/21 12:43:33 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	parse_args(int argc, char **argv);
void	init_app(t_app *app, int argc, char **argv);
void	init_philos(t_philo **philos, t_app *app);
void	inspector(t_app *app);

int	main(int argc, char **argv)
{
	t_app	app;
	t_philo	*philo;

	philo = NULL;
	parse_args(argc, argv);
	init_app(&app, argc, argv);
	init_philos(&philo, &app);
	inspector(&app);
	ensure_threads_terminate(&philo, &app);
	free(philo);
	return (0);
}

void	parse_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		print(NULL, INVALID_ARGS);
	if (argv)
	{
	}
	// int	i;
// int	j;
// i = 0;
// j = 0;
// while (argv[i][j])
// {
// 	while (argv[i][j])
// 	{
// 		if (ft_isdigit(argv[i][j]) == 0)
// 			error_msg_exit();
// 		j++;
// 	}
// 	j = 0;
// 	i++;
// }
}

void	init_app(t_app *app, int argc, char **argv)
{
	app->n_philo = ft_atoi(argv[1]);
	app->time_to_die = ft_atoi(argv[2]);
	app->time_to_eat = ft_atoi(argv[3]);
	app->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		app->max_meals = ft_atoi(argv[5]) * app->n_philo;
	else
	 	app->max_meals = -8;
	app->stop = 0;
	app->start_time = start_curr_time_diff(0);
}

void	init_philos(t_philo **philo, t_app *app)
{
	int	i;

	(*philo) = malloc(app->n_philo * sizeof(t_philo));
	i = -1;
	while (++i < app->n_philo)
	{
		philo[0][i].app = app;
		philo[0][i].id = i + 1;
		pthread_create(&philo[0][i].thread, NULL, philo_circle_of_life, &philo[0][i]);	
	}
}

void	inspector(t_app *app)
{
	while (app->stop == 0)
	{
		if(app->max_meals == 0)
			app->stop = 1;
	}
}