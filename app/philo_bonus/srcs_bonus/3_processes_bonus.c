/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_processes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:45:42 by argel             #+#    #+#             */
/*   Updated: 2022/06/25 14:05:02 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <0_philosophers_bonus.h>

void exit_process(t_philosophers *philo)
{
    if (philo)
    {
        
    }
    exit(0);
}

void create_process(t_philosophers *philo, void (*f)(void *))
{
    philo->pid = fork();
    if (philo->pid == 0)
    {
        f(philo);   
        exit_process(philo);
    }
}

void    wait_processes_finish(t_philosophers **philo)
{
    int i;

    i = -1;
    while (++i < philo[0][0].app->n_philo)
    {
        waitpid(-1, &philo[0][i].exit_code, 0);
        philo[0][i].exit_code = WEXITSTATUS(philo[0][i].exit_code);
    }
    if (philo[0][i].exit_code)
    {
        i = -1;
        while (++i < philo[0][0].app->n_philo)
            kill(philo[0][i].pid, SIGKILL);
    }
}
