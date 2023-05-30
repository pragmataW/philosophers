/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:02:23 by yciftci           #+#    #+#             */
/*   Updated: 2023/05/30 11:04:54 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char opt)
{
	__uint64_t	time;

	pthread_mutex_lock(philo->is_done_mutex);
	pthread_mutex_lock(philo->print_mutex);
	time = get_time() - philo->now;
	if (opt == 'e' && !*(philo->is_done))
	{
		printf("%llu %d has taken a fork\n", time, philo->philo_id);
		printf("%llu %d has taken a fork\n", time, philo->philo_id);
		printf("%llu %d is eating", time, philo->philo_id);
		philo->eating_now = 0;
	}
	else if (opt == 't' && !*(philo->is_done))
		printf("%llu %d is thinking\n", time, philo->philo_id);
	else if (opt == 's' && !*(philo->is_done))
		printf("%llu %d is sleeping\n", time, philo->philo_id);
	else if (opt == 'd')
	{
		ft_usleep(1);
		printf("%llu %d is died\n", time, philo->philo_id);
	}
	pthread_mutex_unlock(philo->is_done_mutex);
	pthread_mutex_unlock(philo->print_mutex);
}
