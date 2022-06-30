/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/29 22:03:56 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

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
	monitor(&philo, &app);
	ensure_threads_terminate(&philo);
	destroy_forks(&app);
	free(app.fork);
	free(philo);
	return (0);
}
