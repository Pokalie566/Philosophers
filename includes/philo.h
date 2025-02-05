/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeboose <adeboose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:07:39 by adeboose          #+#    #+#             */
/*   Updated: 2025/02/05 08:07:40 by adeboose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal;
	int				meals_eaten;
	struct s_data	*data;
	pthread_mutex_t	meal_lock;
}					t_philo;

struct s_data
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
	int				stop;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	long long		start_time;
	pthread_t		monitor;
};

int			init_data(t_data *data, int argc, char **argv);
void		cleanup(t_data *data);
int			check_data(t_data *data, int argc);
int			ft_atoi(const char *str);
long long	get_time(void);
void		print_state(t_philo *philo, const char *state);
void		*philo_routine(void *arg);
void		*monitor(void *arg);
int			init_data(t_data *data, int argc, char **argv);
void		cleanup(t_data *data);
int			ft_atoi(const char *str);
int			check_stop(t_data *data);
void		ft_sleep(long long ms);

#endif
