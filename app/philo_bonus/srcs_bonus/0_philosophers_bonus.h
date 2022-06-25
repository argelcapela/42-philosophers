/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_philosophers_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:09 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/25 15:23:03 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

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
#include <sys/wait.h> 

// usleep, fork
# include <unistd.h>

// kill
#include <signal.h> 

// sem...open,close,wait,post or unlink
#include <semaphore.h>

/**************************************************************************** #
#                                STRUCTS                                      #
# ****************************************************************************/

/**
* Stores many variables necessaries to make the program works well.
* @param
*/
typedef struct s_app
{
	sem_t			*fork;
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
void		finish();

// 2
long int	get_time(long int start);
void		msleep(long int time_to_wait, t_philosophers *philo);

// 3
void		create_process(t_philosophers *philo, void (*f)(void *));
void		wait_processes_finish(t_philosophers **philo);
void 		exit_process(t_philosophers *philo);

// 4
void		routine(void *p_philo);

// 5
void		init_app(t_app *app, int argc, char **argv);
void		init_forks();
void		init_philosophers(t_philosophers **philo, t_app *app);
void		start_routine();

#endif
