/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeboose <adeboose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:48:00 by adeboose          #+#    #+#             */
/*   Updated: 2025/03/05 19:04:55 by adeboose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher_status(t_data *data, int i, int *full_count)
{
	pthread_mutex_lock(&data->philos[i].meal_lock);
	if ((get_time() - data->philos[i].last_meal) > data->time_to_die)
	{
		print_state(&data->philos[i], "is dead");
		pthread_mutex_lock(&data->stop_lock);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_lock);
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		return (1);
	}
	if (data->must_eat != -1 && data->philos[i].meals_eaten >= data->must_eat)
		(*full_count)++;
	pthread_mutex_unlock(&data->philos[i].meal_lock);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;
	int		full_count;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		i = -1;
		full_count = 0;
		while (++i < data->num_philos)
			if (check_philosopher_status(data, i, &full_count))
				return (NULL);
		if (full_count == data->num_philos)
		{
			pthread_mutex_lock(&data->stop_lock);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_lock);
			return (NULL);
		}
		ft_sleep(1, data);
	}
	return (NULL);
}

void	ft_sleep(long long ms, t_data *data)
{
	long long		end_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	end_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) + ms;
	while ((tv.tv_sec * 1000 + tv.tv_usec / 1000) < end_time
		&& !check_stop(data))
	{
		usleep(100);
		gettimeofday(&tv, NULL);
	}
}

int	check_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_lock);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_lock);
	return (stop);
}
