/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:02:19 by yciftci           #+#    #+#             */
/*   Updated: 2023/05/20 15:38:51 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo		**philos;
	int			is_done;

	is_done = 0;
	if (!controls(argc, argv))
	{
		printf("Error!\n");
		return (0);
	}
	philos = init(argc, argv, 0, &is_done);
	destroy(philos);
	return (0);
}
