/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:32:00 by aprotoce          #+#    #+#             */
/*   Updated: 2022/04/10 21:32:00 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_struct(t_env *env, int argc, char **argv);
static void	create_philos(t_philo **philo, t_env *env);
static void	monitor(t_philo **philo, t_env *env);
static void	create_philos(t_philo **philo, t_env *env);

int	main(int argc, char **argv)
{
	t_env		env;
	t_philo		*philo;

	if (argc < 5 || argc > 6)
		print_exit();
	init_struct(&env, argc, argv);
	philo = malloc(env.n_philos * sizeof(t_philo));
	env.fork = malloc(env.n_philos * sizeof(pthread_mutex_t));
	init_mutex(&env);
	create_philos(&philo, &env);
	monitor(&philo, &env);
	join_threads(&philo, &env);
	destroy_mutex(&env);
	free(philo);
	free(env.fork);
	return (0);
}

void	print_exit(void)
{
	printf("philo: Invalid Argument\n\n");
	printf("Usage:\n./philo [n_philo] [time_to_die]");
	printf(" [time_to_eat] [time_to_sleep]");
	printf(" [number_of_times_each_philosopher_must_eat]\n\n");
	exit (1);
}

static void	init_struct(t_env *env, int argc, char **argv)
{
	env->n_philos = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->n_must_eat = ft_atoi(argv[5]);
	else
		env->n_must_eat = 0;
	env->start_time = get_time(0);
	if (!env->n_philos || !env->time_to_die || !env->time_to_eat
		|| !env->time_to_sleep)
		print_exit();
	env->stop = 0;
}

static void	create_philos(t_philo **philo, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->n_philos)
	{
		philo[0][i].env = env;
		philo[0][i].id = i;
		philo[0][i].n_meals = 0;
		philo[0][i].last_meal = get_time(0);
		pthread_create(&philo[0][i].thread, NULL, &lifecicle, &philo[0][i]);
		i++;
	}
}

static void	monitor(t_philo **philo, t_env *env)
{
	int			i;
	int			max_meals;

	i = 0;
	max_meals = 0;
	while (!env->stop)
	{
		if (i == env->n_philos)
		{
			usleep(50);
			i = 0;
		}
		if (get_time(philo[0][i].last_meal) > env->time_to_die)
		{
			env->stop = 1;
			usleep(500);
			print(&philo[0][i], DIE);
		}
		if (philo[0][i].n_meals == env->n_must_eat &&
			env->n_must_eat > 0)
			max_meals++;
		if (max_meals == env->n_philos)
			env->stop = 1;
		i++;
	}
}
