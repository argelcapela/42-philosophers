/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_circle_of_life.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/21 09:44:57 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void  philo_eat(t_philo *philo);
static void  philo_sleep(t_philo *philo);
static void  philo_think(t_philo *philo);

void *philo_circle_of_life(void *p_philo)
{
    t_philo *philo;

    philo = (t_philo *) p_philo;
    while (philo->app->stop == 0)
    {
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}

static void  philo_eat(t_philo *philo)
{
    print(philo, EAT);
    usleep(50);
    if(philo->app->max_meals != -8)
        philo->app->max_meals -= 1;
}

static void  philo_sleep(t_philo *philo)
{
    print(philo, SLEEP);
    usleep(50);
}

static void  philo_think(t_philo *philo)
{
    print(philo, THINK);
    usleep(50);
}

