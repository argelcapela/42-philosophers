/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_exit_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:00:28 by argel             #+#    #+#             */
/*   Updated: 2022/06/30 21:26:52 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

void	exit_app(t_app *app)
{
	sem_close(app->lock_print);
	sem_close(app->forks);
	sem_unlink("/lock_print");
	sem_unlink("/forks");
	exit(0);
}

void	exit_process(t_philosophers **philo, int exit_code)
{
	sem_close((*philo)->app->lock_print);
	sem_close((*philo)->app->forks);
	sem_unlink("/lock_print");
	sem_unlink("/forks");
	free(*philo);
	exit(exit_code);
}
