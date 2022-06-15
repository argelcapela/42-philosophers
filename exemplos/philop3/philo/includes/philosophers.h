/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:11:39 by aprotoce          #+#    #+#             */
/*   Updated: 2022/04/10 21:11:39 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
** Used to identify the message to be printed to the terminal
*/
# define FORK	0
# define EAT	1
# define SLEEP	2
# define THINK	3
# define DIE	4

/**
* Stores the arguments provided with the program call
* and the environment variables
* @param fork An array containing all the mutexes for the forks
* @param n_philos Provided param number_of_philosophers
* @param time_to_die Provided param time_to_die
* @param time_to_eat Provided param time_to_eat
* @param time_to_sleep Provided param time_to_sleep
* @param n_must_eat Provided param number_of_times_each_philosopher_must_eat
* @param start_time The time the program started (in milliseconds)
* @param stop Variable used to stop the simulation
*/
typedef struct s_environment
{
	pthread_mutex_t	*fork;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_must_eat;
	long int		start_time;
	int				stop;
}	t_env;

/**
* Stores the data of each philosopher
* @param env A pointer to the t_env struct
* @param thread Identifies the philosopher's thread
* @param id An int identifying the phgilosopher
* @param last_meal Timestamp (in milliseconds) of the last finished meal
* @param n_meals Number of completed meals
*/
typedef struct s_philosopher
{
	t_env			*env;
	pthread_t		thread;
	int				id;
	long int		last_meal;
	int				n_meals;
}	t_philo;


void		print_exit(void);

/*
** lifecicle.c
*/
/**
* The start routine to the lifecicle of each philosopher
* @param arg A pointer to the philosopher struct
*/
void		*lifecicle(void *arg);

/*
** threads.c
*/
/**
* Initiate all the foks mutexes
* @param env A pointer to the t_env struct
*/
void		init_mutex(t_env *env);

/**
* Destroy all the foks mutexes
* @param env A pointer to the t_env struct
*/
void		destroy_mutex(t_env *env);

/**
* Join all the philosopers threads
* @param philo The matrix containing all the philosopers structs
* @param env A pointer to the t_env struct
*/
void		join_threads(t_philo **philo, t_env *env);

/*
** utils.c
*/
/**
* Constructs an integer from a string
* @param nptr Is the string representing the number
* @return The converted int; 0 when the string does not contains a valid integer
*/
int			ft_atoi(const char *nptr);

/**
* Returns the time, in milliseconds, or the difference between the local time
* and the start time
* @param start The time, in milliseconds, to be compared to the local time
* @return If start time is provided, returns the time difference.
* Otherwise returns the time in milliseconds
*/
long int	get_time(long int start);

/*
** print.c
*/
/**
* Prints a message to the terminal
* @param philo A pointer to the philo struct
* @param action A number identifying the action message
*/
void		print(t_philo *philo, int action);

/**
* Prints a usage message to the terminal and exit the program
*/
void		print_exit(void);

#endif
