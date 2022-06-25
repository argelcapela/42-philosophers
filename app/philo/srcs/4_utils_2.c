/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/25 08:16:40 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
* As the function name says, it return the difference between
* current time in miliseconds and app->start_time (stored at 
* the beginning) also in miliseconds. It is used in each print
* of philo_circle_of_life creating allowing to print the exact
* miliseconds that each action was executed since the start of
* the application, always increasing until the app terminate.
*
*	- epoch: 1970, 00:00:00, Unix standard date.
*	- gettimeofday: get amount of microseconds from EPOCH until
*	your current time.
*	- timer.tv_sec: seconds
*	- timer.tv_usec: miliseconds
* @param timer struct that store the result from gettimeofday
* @param start_time generaly will be the app->start_time value
* which is the time application started, or zero, when this func-
* be called for the first time.
* @param current_time is literaly the current_time of the system
* @line 42 
* @line 43
*/
long int	get_time(long int last_meal_or_action_time)
{
	struct timeval	tv;
	long int		secon_to_mili;
	long int		micro_to_mili;
	long int		current_time;

	gettimeofday(&tv, NULL);
	secon_to_mili = tv.tv_sec * 1000;
	micro_to_mili = tv.tv_usec / 1000;
	current_time = secon_to_mili + micro_to_mili;
	if (last_meal_or_action_time != 0)
		current_time -= last_meal_or_action_time;
	return (current_time);
}

/**
* Print error msgs or the philosophers state in theirs circle of life.
* @param philo Memory Block where all the philos are stored.
* @param state CONSTANT value defined in philo.h, that represent the state to be
* printed.
* @line 52 - '%5.3ld':
*	- .3: It's [precision], so the number printed need to have at least 3 digits
*	or zeros will be added before it. For example, instead of 1, will be printed
*	001.
*	- 5: It's [field width], so if the number printed is smaller than 5 digits
*	will be added spaces until fill 5 digits. For example, intead of 001, will be
*	printed "  001".
*	- li: l converts an long(int32) value to the second letter type specified,
*	in this case long printed as integer.
*/
void	print(t_philo *philo, int state)
{
	char		*msg[6];
	long int	tmp;

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
	else if ((philo->app->stop && state == DIE))
	{
		tmp = get_time(philo->app->start_time);
		if (philo->app->n_philo > 1)
			tmp -= 2;
		printf("%5.3ld\t%d %s\n", tmp - 1, philo->id + 1, msg[state]);
	}
	else if (!philo->app->stop)
		printf("%5.3ld\t%d %s\n", \
get_time(philo->app->start_time), philo->id + 1, msg[state]);
}