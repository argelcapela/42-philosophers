/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _philo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:09 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/29 22:06:17 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H
# define _PHILO_H

/**************************************************************************** #
#                                   LIBS                                      #
# ****************************************************************************/

// malloc, free
# include <stdlib.h>

// printf
# include <stdio.h>

// gettimeofday
# include <sys/time.h>

// usleep
# include <unistd.h>

// t_thread, pthread_create, pthread_join
// t_mutex, t_mutex_lock, t_mutex_unlock
# include <pthread.h>

/**************************************************************************** #
#                                STRUCTS                                      #
# ****************************************************************************/

/**
* Stores many variables necessaries to make the program works well.
* @param
*/
typedef struct s_app
{
	pthread_mutex_t	*lock_time;
	pthread_mutex_t	*fork;
	int				n_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				max_meals_by_philo;
	int				max_meals;
	int				stop;
	long int		start_time;
}	t_app;

/**
* This struct works like Object Oriented Programming and represents
* each philosopher.
* @param 
*/
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_app			*app;
	long int		last_meal_time;
	int				meals;
}	t_philo;

/**************************************************************************** #
#                                CONSTANTS                                    #
# ****************************************************************************/

# define FORK 			0
# define EAT  			1
# define SLEEP  		2
# define THINK  		3
# define DIE  			4
# define INVALID_ARGS  	5

/**************************************************************************** #
#                                PROTOTYPES                                   #
# ****************************************************************************/

// 1
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		print(t_philo *philo, int state);

// 2
long int	get_time(long int start);

// 3
void		destroy_forks(t_app *app);
void		ensure_threads_terminate(t_philo **philo);

// 4
void		*routine(void *p_philo);

// 5
void		monitor(t_philo **philo, t_app *app);

// 6
void		init_app(t_app *app, int argc, char **argv);
void		init_forks(t_app *app);
void		init_philos(t_philo **philo, t_app *app);

#endif
