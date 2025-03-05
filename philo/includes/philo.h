/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeboose <adeboose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:07:39 by adeboose          #+#    #+#             */
/*   Updated: 2025/03/05 17:49:39 by adeboose         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                 Data Structures                            */
/* ************************************************************************** */

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

typedef struct s_data
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
	const char		*clock_emojis[12];
	int				clock_index;
	int				philos_completed;
	pthread_mutex_t	meals_complete_lock;
}					t_data;

/* ************************************************************************** */
/*                            Function Prototypes                             */
/* ************************************************************************** */

int			init_data(t_data *data, int argc, char **argv);
void		cleanup(t_data *data);
int			check_data(t_data *data, int argc);
int			ft_atoi(const char *str);
long long	get_time(void);
void		print_state(t_philo *philo, char *state);
void		*philo_routine(void *arg);
void		*monitor(void *arg);
int			check_stop(t_data *data);
void		ft_sleep(long long ms, t_data *data);
void		init_emojis(t_data *data);
void		philo_lifecycle(t_philo *philo);
int			ft_strcmp(char *s1, char *s2);
void		*ft_memcpy(void *dest, const void *src, size_t n);

#endif /* PHILO_H */
