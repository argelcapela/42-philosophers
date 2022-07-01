/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_processes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:45:42 by argel             #+#    #+#             */
/*   Updated: 2022/07/01 08:44:26 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

void	create_process(t_philosophers *philo, \
int (*f)(t_philosophers *), t_philosophers **s_philo)
{
	int	exit_code;

	exit_code = 0;
	philo->pid = fork();
	if (philo->pid == 0)
	{
		exit_code = f(philo);
		exit_process(s_philo, exit_code);
	}
}

void	wait_processes_finish(t_philosophers **philo)
{
	int	i;
	int	exit_code;

	i = -1;
	exit_code = 0;
	while (++i < philo[0][0].app->n_philo && exit_code == 0)
	{
		waitpid(-1, &exit_code, 0);
		exit_code = WEXITSTATUS(exit_code);
	}
	i = -1;
	if (exit_code)
	{
		while (++i < philo[0][0].app->n_philo)
			kill(philo[0][i].pid, SIGKILL);
	}
}
