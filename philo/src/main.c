/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeboose <adeboose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 04:21:55 by adeboose          #+#    #+#             */
/*   Updated: 2025/02/06 07:50:17 by adeboose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meals_eaten = 0;
		pthread_mutex_init(&data->philos[i].meal_lock, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc < 5 || argc > 6)
		return (printf("Error: wrong args\n"), 1);
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argc, argv))
		return (1);
	if (check_data(&data, argc))
		return (1);
	data.start_time = get_time();
	init_philos(&data);
	i = -1;
	while (++i < data.num_philos)
		pthread_create(&data.philos[i].thread, NULL, philo_routine,
			&data.philos[i]);
	pthread_create(&data.monitor, NULL, monitor, &data);
	i = -1;
	while (++i < data.num_philos)
		pthread_join(data.philos[i].thread, NULL);
	pthread_join(data.monitor, NULL);
	cleanup(&data);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int		i;

	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->stop = 0;
	data->start_time = 0;
	init_emojis(data);
	data->clock_index = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks || !data->philos)
		return (1);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->stop_lock, NULL);
	data->philos_completed = 0;
	pthread_mutex_init(&data->meals_complete_lock, NULL);
	i = 0;
	while (i < data->num_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->stop_lock);
	pthread_mutex_destroy(&data->meals_complete_lock);
	free(data->forks);
	free(data->philos);
}

int	check_data(t_data *data, int argc)
{
	if (data->num_philos <= 0)
		return (1);
	if (data->time_to_die <= 0)
		return (1);
	if (data->time_to_eat <= 0)
		return (1);
	if (data->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		if (data->must_eat <= 0)
			return (1);
	}
	return (0);
}
