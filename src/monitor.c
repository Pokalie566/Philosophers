/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeboose <adeboose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:48:00 by adeboose          #+#    #+#             */
/*   Updated: 2025/02/06 07:59:23 by adeboose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals(t_data *data)
{
	if (data->must_eat == -1)
		return (0);
	pthread_mutex_lock(&data->meals_complete_lock);
	if (data->philos_completed >= data->num_philos)
	{
		pthread_mutex_lock(&data->print_lock);
		printf("\nAll philosophers have finished eating %d times.\n",
			data->must_eat);
		pthread_mutex_unlock(&data->print_lock);
		pthread_mutex_lock(&data->stop_lock);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_lock);
		pthread_mutex_unlock(&data->meals_complete_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->meals_complete_lock);
	return (0);
}

static int	check_philosopher_status(t_data *data, int i)
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
	pthread_mutex_unlock(&data->philos[i].meal_lock);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		i = -1;
		while (++i < data->num_philos)
			if (check_philosopher_status(data, i))
				return (NULL);
		if (check_meals(data))
			return (NULL);
		ft_sleep(1);
	}
	return (NULL);
}
