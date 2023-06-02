/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:01:52 by yciftci           #+#    #+#             */
/*   Updated: 2023/05/17 16:01:53 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init(int argc, char *argv[], uint64_t i, int *is_done)
{
	t_philo			**philos;
	pthread_t		*threads;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	last_eat_mutex;

	threads = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	mutexes = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	philos = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	pthread_mutex_init(&print_mutex, NULL);
	pthread_mutex_init(&last_eat_mutex, NULL);
	init_mutexes(mutexes, ft_atoi(argv[1]), philos, ft_atoi(argv[1]));
	is_done_mutexes(philos, ft_atoi(argv[1]));
	while (i < ft_atoi(argv[1]))
	{
		init_data(argc, argv, philos[i], i);
		philos[i]->philo = &threads[i];
		philos[i]->print_mutex = &print_mutex;
		philos[i]->last_eat_mutex = &last_eat_mutex;
		philos[i]->is_done = is_done;
		i++;
	}
	init_threads(threads, ft_atoi(argv[1]), philos, argv);
	return (philos);
}

void	init_data(int argc, char *argv[], t_philo *philo, int philo_id)
{
	philo->philo_id = philo_id;
	philo->philo_count = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->needle_eat = ft_atoi(argv[3]);
	philo->needle_sleep = ft_atoi(argv[4]);
	philo->must_eat = -1;
	philo->last_eat = 0;
	philo->eating_now = 0;
	philo->now = get_time();
	if (argc == 6)
		philo->must_eat = ft_atoi(argv[5]);
}

void	init_threads(pthread_t *thread, int p_count, t_philo **philos, char **a)
{
	int			i;
	pthread_t	*dead_check;
	pthread_t	*all_ate_thread;
	t_socrates	*socrates;

	i = -1;
	socrates = malloc(sizeof(t_socrates));
	all_ate_thread = malloc(sizeof(pthread_t));
	dead_check = malloc(sizeof(pthread_t));
	socrates->argv = a;
	socrates->philos = philos;
	pthread_create(dead_check, NULL, finish_dinner, socrates);
	pthread_create(all_ate_thread, NULL, all_ate, socrates);
	while (++i < p_count)
		pthread_create(&thread[i], NULL, life_cycle, philos[i]);
	i = -1;
	pthread_join(*dead_check, NULL);
	pthread_join(*all_ate_thread, NULL);
	while (++i < p_count)
		pthread_join(*(philos[i]->philo), NULL);
	while (--i >= 0)
	{
		philos[i]->all_ate_thread = all_ate_thread;
		philos[i]->dead_check = dead_check;
	}
}

void	init_mutexes(pthread_mutex_t *mutex, int ph_c, t_philo **ph, int i)
{
	pthread_mutex_t	*last_eat_mutexes;

	last_eat_mutexes = malloc(sizeof(pthread_mutex_t));
	while (i-- > 0)
	{
		pthread_mutex_init(&last_eat_mutexes[i], NULL);
		pthread_mutex_init(&mutex[i], NULL);
	}
	while (i++ < ph_c)
	{
		ph[i] = malloc(sizeof(t_philo));
		ph[i]->last_eat_mutex = &last_eat_mutexes[i];
		if (i != ph_c - 1)
		{
			ph[i]->r_fork = &(mutex[i]);
			ph[i]->l_fork = &(mutex[i + 1]);
		}
		else
		{
			ph[i]->r_fork = &(mutex[i]);
			ph[i]->l_fork = &(mutex[0]);
		}
	}
}

void	is_done_mutexes(t_philo **philos, int philo_count)
{
	pthread_mutex_t	*is_done_mutex;
	int				i;

	is_done_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(is_done_mutex, NULL);
	i = 0;
	while (i < philo_count)
	{
		philos[i]->is_done_mutex = is_done_mutex;
		i++;
	}
}
