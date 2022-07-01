/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_main_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/07/01 15:09:41 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

int	main(int argc, char **argv)
{
	t_app			app;
	t_philosophers	*philo;

	if (argc < 5 || argc > 6)
		invalid_args();
	init_app(&app, argc, argv);
	philo = malloc(app.n_philo * sizeof(t_philosophers));
	init_philosophers(&philo, &app);
	init_forks(&philo);
	start_routine(&philo);
	free(philo);
	exit_app(&app);
	return (0);
}
