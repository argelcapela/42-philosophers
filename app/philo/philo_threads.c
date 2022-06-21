/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/21 16:03:01 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    ensure_threads_terminate(t_philo **philo, t_app *app)
{
    int i;

    i = 0;
    while (++i < app->n_philo)
    {
       pthread_join(philo[0][i].thread, NULL);
       i++;
    }
}

void    init_forks(t_app *app)
{
    int i;

    app->fork = malloc(app->n_philo * \
sizeof(pthread_mutex_t));
    i = 0;
    while (i < app->n_philo)
    {
        pthread_mutex_init(&app->fork[i], NULL);
        i++;
    }
}

void    destroy_forks(t_app *app)
{
    int i;

    i = 0;
    while (i < app->n_philo)
    {
        pthread_mutex_destroy(&app->fork[i]);
        i++;
    }
}