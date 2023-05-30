/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:02:16 by yciftci           #+#    #+#             */
/*   Updated: 2023/05/30 10:43:49 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_id;
	pthread_t		*philo;
	pthread_t		*dead_check;
	pthread_t		*all_ate_thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*last_eat_mutex;
	pthread_mutex_t	*is_done_mutex;
	__uint64_t		last_eat;
	__uint64_t		needle_eat;
	__uint64_t		needle_sleep;
	__uint64_t		time_to_die;
	int				must_eat;
	int				eating_now;
	int				philo_count;
	int				eat_count;
	uint64_t		now;
	int				*is_done;
}				t_philo;

typedef struct s_socrates
{
	struct s_philo	**philos;
	char			**argv;
}			t_socrates;

//utils
uint64_t	ft_atoi(char *str);
int			ft_isnum(char *num);
//error_management
int			controls(int argc, char *argv[]);
//life_cycle
void		*life_cycle(void *nullable);
void		eating(t_philo *philo);
//init
t_philo		**init(int argc, char *argv[], uint64_t i, int *is_done);
void		init_data(int argc, char *argv[], t_philo *philo, int philo_id);
void		init_threads(pthread_t *t, int p_c, t_philo **philos, char **a);
void		init_mutexes(pthread_mutex_t *mutex, int ph_c, t_philo **ph, int i);
void		is_done_mutexes(t_philo **philos, int philo_count);
//print
void		print(t_philo *philo, char opt);
//time
__uint64_t	get_time(void);
void		ft_usleep(uint64_t need_to_wait);
//finishdinner
void		*finish_dinner(void *socrates);
void		*all_ate(void *data);
//destroy
void		destroy(t_philo **socrates);
#endif
