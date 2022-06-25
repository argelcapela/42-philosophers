/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_main_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/25 12:45:26 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <0_philosophers_bonus.h>

int	main(int argc, char **argv)
{
	t_app			app;
	t_philosophers	*philo;

	if (argc < 5 || argc > 6)
		print(NULL, INVALID_ARGS);
	init_app(&app, argc, argv);
	philo = malloc(app.n_philo * sizeof(t_philosophers));
	init_philosophers(&philo, &app);
	init_forks();
	start_routine(&philo);
	return (0);
}
