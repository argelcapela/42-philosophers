/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/21 09:25:34 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    ensure_threads_terminate(t_philo **philo, t_app *app)
{
    int i;

    i = -1;
    while (++i < app->n_philo)
       pthread_join(philo[0][i].thread, NULL);
}