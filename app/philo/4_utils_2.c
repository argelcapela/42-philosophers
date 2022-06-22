/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/22 14:31:33 by argel            ###   ########.fr       */
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
long int	get_time(long int start_time)
{
	struct timeval	timer;
	long int		current_time;

	gettimeofday(&timer, NULL);
	current_time = timer.tv_sec * 1000;
	current_time += timer.tv_usec / 1000;
	if (start_time)
		current_time -= start_time;
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
	char	*msg[6];

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
		ft_putstr_fd(msg[5], 1);
		exit(1);
	}
	else
	{
		pthread_mutex_lock(&philo->app->write_m);
		ft_putnbr_fd(get_time(philo->app->start_time), 1);
		write(1, "\t", 1);
		ft_putnbr_fd(philo->id + 1, 2);
		write(1, " ", 1);
		ft_putstr_fd(msg[state], 1);
		write(1, "\n", 1);
		pthread_mutex_unlock(&philo->app->write_m);
	}
}

void	init_forks(t_app *app)
{
	int	i;

	app->fork = malloc(app->n_philo * \
sizeof(pthread_mutex_t));
	i = 0;
	pthread_mutex_init(&app->write_m, NULL);
	while (i < app->n_philo)
	{
		pthread_mutex_init(&app->fork[i], NULL);
		i++;
	}
}

void	destroy_forks(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->n_philo)
	{
		pthread_mutex_destroy(&app->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&app->write_m);
}

void	exit_free(t_philo **philo)
{
	ensure_threads_terminate(philo);
	destroy_forks((*philo)->app);
	free((*philo)->app->fork);
	free((*philo));
	exit(0);
}