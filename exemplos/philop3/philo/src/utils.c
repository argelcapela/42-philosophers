/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:25:48 by aprotoce          #+#    #+#             */
/*   Updated: 2022/04/10 21:25:48 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print(t_philo *philo, int action)
{
	static char	*message[5] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	if (!philo->env->stop || (philo->env->stop && action == DIE))
		printf("%5.3ld %5d %s\n",
			get_time(philo->env->start_time), philo->id + 1, message[action]);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (8192);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	long int	ret;
	int			signal;

	ret = 0;
	signal = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		ret *= 10;
		ret += *nptr - 48;
		nptr++;
		if (ret > 2147483647 && signal == 1)
			return (-1);
		if (ret > 2147483648 && signal == -1)
			return (0);
	}
	return ((int)ret * signal);
}

long int	get_time(long int start)
{
	struct timeval	tp;
	long int		time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000;
	time += tp.tv_usec / 1000;
	if (start)
		time -= start;
	return (time);
}
