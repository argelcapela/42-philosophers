/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_utils_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/30 13:00:12 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philosophers_bonus.h>

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	s;
	int	i;
	int	res;

	s = 1;
	i = 0;
	res = 0;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			s *= -1;
		}
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * s);
}

/**
* Print error msgs or the philosophers state, during
* philosphers routine execution.
* @param philo pointer to the varible holding all philosophers
* @param state constant int variable that indicades the state
* @see [sem_wait or sem_post] are used to block any other 
message to be printed, inside this isolated process,
after someone died. This allow us to pause this process,
until this process be killed.
*/
void	print(t_philosophers *philo, int state)
{
	char		*msg[6];
	long int	current_time;

	msg[0] = "has taken a fork";
	msg[1] = "is eating";
	msg[2] = "is sleeping";
	msg[3] = "is thinking";
	msg[4] = "died";
	msg[5] = "Invalid argument, please try again! \n\nexample:\n \
./philo [number_of_philosophers] [time_to_die] [time_to_eat] \
[time_to_sleep] [number_of_times_each_philosopher_must_eat]\n\n";
	if (philo == NULL && state == INVALID_ARGS)
	{
		printf("%s", msg[5]);
		exit(1);
	}
	sem_wait(philo->app->lock_print);
	current_time = get_time_passed_since(philo->app->start_time);
	printf("%5ld\t%d %s\n", current_time, philo->id + 1, msg[state]);
	if (state != DIE)
		sem_post(philo->app->lock_print);
}
