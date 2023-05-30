/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:01:28 by yciftci           #+#    #+#             */
/*   Updated: 2023/05/20 15:49:07 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < philos[i]->philo_count)
	{
		pthread_mutex_destroy(philos[i]->r_fork);
		pthread_mutex_destroy(philos[i]->last_eat_mutex);
		i++;
	}
	pthread_mutex_destroy(philos[0]->is_done_mutex);
	pthread_mutex_destroy(philos[0]->print_mutex);
	pthread_detach(*(philos[0]->all_ate_thread));
	pthread_detach(*(philos[0]->dead_check));
}
