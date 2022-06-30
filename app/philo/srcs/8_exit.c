/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:44:33 by argel             #+#    #+#             */
/*   Updated: 2022/06/30 09:56:47 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

void	exit_app(t_app *app, t_philosophers *philo, \
int exit_code)
{
	if (exit_code)
		exit(exit_code);
	else
	{
		destroy_forks(app);
		free(app->fork);
		free(philo);
		exit(exit_code);
	}
}
