/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _philosophers_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:09 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/29 21:45:51 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILOSOPHERS_BONUS_H
# define _PHILOSOPHERS_BONUS_H

/**************************************************************************** #
#                                   LIBS                                      #
# ****************************************************************************/

// malloc, free
# include <stdlib.h>

// printf
# include <stdio.h>

// gettimeofday
# include <sys/time.h>

// waitpid
# include <sys/wait.h> 

// usleep, fork
# include <unistd.h>

// kill
# include <signal.h> 

// sem...open,close,wait,post or unlink
# include <semaphore.h>

// O_CREAT
# include <fcntl.h>

/**************************************************************************** #
#                                STRUCTS                                      #
# ****************************************************************************/

/**
* Stores many variables necessaries to make the program works well.
* @param
*/
typedef struct s_app
{
	sem_t			*lock_time;
	sem_t			*forks;
	sem_t			*lock_print;
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
typedef struct s_philosophers
{
	int				id;
	pid_t			pid;
	int				exit_code;
	long int		last_meal_time;
	int				meals;
	int				name;
	t_app			*app;
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

// 2
long int	get_time(long int start);
void		dsleep(int time_in_ms, t_philosophers *philo);
void		msleep(int time_in_ms);
long		timestamp(void);
long		timenow(long firststamp);

// 3
void		create_process(t_philosophers *philo, int (*f)(t_philosophers **));
void		wait_processes_finish(t_philosophers **philo);

// 4
int			routine(t_philosophers **p_philo);

// 5
void		init_app(t_app *app, int argc, char **argv);
void		init_forks(t_philosophers **philo);
void		init_philosophers(t_philosophers **philo, t_app *app);
void		monitor(t_philosophers **philo, t_app *app);
void		start_routine(t_philosophers **philo);

// 6
void		exit_app(t_philosophers *philo);
void		stop_routine(t_philosophers *philo, int exit_code);

#endif
