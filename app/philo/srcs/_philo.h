/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _philo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:09 by acapela-          #+#    #+#             */
/*   Updated: 2022/07/01 14:47:30 by acapela-         ###   ########.fr       */
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
	pthread_mutex_t	lock_meal;
	pthread_mutex_t	lock_time;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_app;
	pthread_mutex_t	lock_any;
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
	t_app			*app;
	long int		last_meal_time;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philosophers;

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
void		print(t_philosophers *philo, int state);
void		invalid_args(void);

// 2
long		time_now(void);
long		get_time_passed_since(long int start_time);
void		check_starvation(int i, t_philosophers **philo, t_app *app);

// 3
void		destroy_forks(t_app *app);
void		wait_threads_exit(t_philosophers **philo);

// 4
void		*routine(void *p_philo);

// 5
void		monitor(t_philosophers **philo, t_app *app);

// 6
void		init_app(t_app *app, int argc, char **argv);
void		init_forks(t_app *app);
void		init_philosophers(t_philosophers **philo, t_app *app);

// 7
void		exit_app(t_app *app, t_philosophers *philo, \
int exit_code);

#endif
