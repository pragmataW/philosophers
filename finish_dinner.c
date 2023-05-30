/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:01:41 by yciftci           #+#    #+#             */
/*   Updated: 2023/05/30 11:02:17 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_dinner_extra(t_socrates *socrates)
{
	pthread_mutex_lock(socrates->philos[0]->is_done_mutex);
	if (*(socrates->philos[0]->is_done) == 1)
	{
		pthread_mutex_unlock(socrates->philos[0]->is_done_mutex);
		return (1);
	}
	pthread_mutex_unlock(socrates->philos[0]->is_done_mutex);
	return (0);
}

void	*finish_dinner(void *socrates)
{
	uint64_t	i;
	t_socrates	*data;

	data = (t_socrates *)socrates;
	while (1)
	{
		i = -1;
		if (finish_dinner_extra(data))
			return (NULL);
		while (++i < ft_atoi(data->argv[1]))
		{
			pthread_mutex_lock(data->philos[i]->last_eat_mutex);
			if (get_time() - data->philos[i]->last_eat >= ft_atoi(data->argv[2])
				&& data->philos[i]->last_eat != 0)
			{
				pthread_mutex_unlock(data->philos[i]->last_eat_mutex);
				pthread_mutex_lock(data->philos[0]->is_done_mutex);
				*(data->philos[i]->is_done) = 1;
				pthread_mutex_unlock(data->philos[0]->is_done_mutex);
				print(data->philos[i], 'd');
				return (NULL);
			}
			pthread_mutex_unlock(data->philos[i]->last_eat_mutex);
		}
	}
}

int	all_ate_control(t_philo **philos)
{
	int		i;

	i = 0;
	while (i < philos[0]->philo_count)
	{
		pthread_mutex_lock(philos[i]->last_eat_mutex);
		if (philos[i]->must_eat > 0 && philos[i]->must_eat != -1)
		{
			pthread_mutex_unlock(philos[i]->last_eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(philos[i]->last_eat_mutex);
		i++;
	}
	return (1);
}

void	*all_ate(void *data)
{
	t_socrates	*socrates;

	socrates = (t_socrates *)data;
	pthread_mutex_lock(socrates->philos[0]->is_done_mutex);
	while (*(socrates->philos[0]->is_done) == 0)
	{
		pthread_mutex_unlock(socrates->philos[0]->is_done_mutex);
		if (all_ate_control(socrates->philos) == 1)
		{
			pthread_mutex_lock(socrates->philos[0]->is_done_mutex);
			*(socrates->philos[0]->is_done) = 1;
			pthread_mutex_unlock(socrates->philos[0]->is_done_mutex);
			return (NULL);
		}
		pthread_mutex_lock(socrates->philos[0]->is_done_mutex);
	}
	pthread_mutex_unlock(socrates->philos[0]->is_done_mutex);
	return (NULL);
}
