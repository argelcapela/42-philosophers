/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:09 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/21 12:52:34 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

/***************************************************************************** #
#                                   LIBS                                       #
# *****************************************************************************/

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

/***************************************************************************** #
#                                STRUCTS                                       #
# *****************************************************************************/

/**
* Stores many variables necessaries to make the program works well.
* @param
*/
typedef struct s_app{
	int 		n_philo;
	int 		time_to_eat;
	int 		time_to_sleep;
	int 		time_to_die;
	int 		max_meals;
	int			stop;
	long int	start_time;
} t_app;

/**
* This struct works like Object Oriented Programming and represents
* each philosopher.
* @param 
*/
typedef struct s_philo{
	int			id;
	pthread_t   thread;
	t_app		*app;	
} t_philo;

/***************************************************************************** #
#                                CONSTANTS                                     #
# *****************************************************************************/

# define FORK 			0
# define EAT  			1
# define SLEEP  		2
# define THINK  		3
# define DIE  			4
# define INVALID_ARGS  	5

/***************************************************************************** #
#                          PHILO_CIRCLE_OF_LIFE.C                              #
# *****************************************************************************/
void	*philo_circle_of_life(void *p_philo);

/***************************************************************************** #
#                             PHILO_THREADS.C                                  #
# *****************************************************************************/
void    ensure_threads_terminate(t_philo **philo, t_app *app);

/***************************************************************************** #
#                              PHILO_UTILS.C                                   #
# *****************************************************************************/
long int	start_curr_time_diff(long int start);
void		print(t_philo *philo, int state);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);

#endif
