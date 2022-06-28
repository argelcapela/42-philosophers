/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_exit_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:00:28 by argel             #+#    #+#             */
/*   Updated: 2022/06/28 10:25:50 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

void	exit_app(t_philosophers *philo)
{
	sem_close(philo->app->lock_print);
	sem_close(philo->app->forks);
	sem_unlink("/lock_print");
	sem_unlink("/forks");
	exit(0);
}

void	stop_routine(t_philosophers *philo, int exit_code)
{
	sem_close(philo->app->lock_print);
	sem_close(philo->app->forks);
	sem_unlink("/lock_print");
	sem_unlink("/forks");
	exit(exit_code);
}
