/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/07/01 14:53:15 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_philo.h>

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
*/
void	print(t_philosophers *philo, int state)
{
	char		*msg[5];

	pthread_mutex_lock(&philo->app->lock_app);
	msg[0] = "has taken a fork";
	msg[1] = "is eating";
	msg[2] = "is sleeping";
	msg[3] = "is thinking";
	msg[4] = "died";
	if ((philo->app->stop && state == DIE) || !philo->app->stop)
		printf("%5.3ld\t%d %s\n", get_time_passed_since(philo->app->start_time), \
philo->id + 1, msg[state]);
	pthread_mutex_unlock(&philo->app->lock_app);
}

void	invalid_args(void)
{
	printf("Invalid argument, please try again! \n\nexample:\n \
./philo [number_of_philosophers] [time_to_die] [time_to_eat] \
[time_to_sleep] [number_of_times_each_philosopher_must_eat]\n\n");
	exit(1);
}
