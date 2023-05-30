/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:01:33 by yciftci           #+#    #+#             */
/*   Updated: 2023/05/17 16:01:34 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	controls(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (argv[i])
	{
		if (!ft_isnum(argv[i]))
			return (0);
		i++;
	}
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) < 1)
		return (0);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (0);
	if (ft_atoi(argv[1]) == 1)
	{
		printf("Philo 1, took the right fork\n");
		printf("Error! Philo 1 didn't get the left fork\n");
		ft_usleep(ft_atoi(argv[2]));
		printf("Philo 1 is dead");
		return (0);
	}
	return (1);
}
