/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/07/01 14:47:04 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

int	main(int argc, char **argv)
{
	t_app			app;
	t_philosophers	*philo;

	if (argc < 5 || argc > 6)
		invalid_args();
	init_app(&app, argc, argv);
	philo = malloc(app.n_philo * sizeof(t_philosophers));
	init_forks(&app);
	init_philosophers(&philo, &app);
	monitor(&philo, &app);
	wait_threads_exit(&philo);
	exit_app(&app, philo, 0);
	return (0);
}
