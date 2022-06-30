/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/30 09:58:56 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

int	main(int argc, char **argv)
{
	t_app			app;
	t_philosophers	*philo;

	if (argc < 5 || argc > 6)
		print(NULL, INVALID_ARGS);
	init_app(&app, argc, argv);
	philo = malloc(app.n_philo * sizeof(t_philosophers));
	init_forks(&app);
	init_philosophers(&philo, &app);
	monitor(&philo, &app);
	wait_threads_exit(&philo);
	exit_app(&app, philo, 0);
	return (0);
}
