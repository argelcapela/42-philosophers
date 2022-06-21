/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_circle_of_life.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/20 20:45:39 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void  philo_eat(t_philo *philo);
static void  philo_sleep(t_philo *philo);
static void  philo_think(t_philo *philo);

void philo_circle_of_life(void *p_philo)
{
    t_philo *philo;

    philo = (t_philo *) p_philo;
    philo_eat(philo);
    philo_sleep(philo);
    philo_think(philo);
}

static void  philo_eat(t_philo *philo)
{
    print(philo, EAT);
}

static void  philo_sleep(t_philo *philo)
{
    print(philo, SLEEP);
}

static void  philo_think(t_philo *philo)
{
    print(philo, THINK);
}

