/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeboose <adeboose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:07:45 by adeboose          #+#    #+#             */
/*   Updated: 2025/02/06 08:05:59 by adeboose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken the left fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken the right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken the right fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken the left fork");
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->data->must_eat != -1
		&& philo->meals_eaten >= philo->data->must_eat)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return ;
	}
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_state(philo, "is eating");
	ft_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meals_complete_lock);
	if (philo->data->must_eat != -1
		&& philo->meals_eaten >= philo->data->must_eat)
	{
		philo->data->philos_completed++;
		pthread_mutex_lock(&philo->data->stop_lock);
		if (philo->data->philos_completed >= philo->data->num_philos)
			philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->stop_lock);
	}
	pthread_mutex_unlock(&philo->data->meals_complete_lock);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_sleep(philo->data->time_to_eat / 2);
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken the left fork");
		ft_sleep(philo->data->time_to_die);
		return (NULL);
	}
	philo_lifecycle(philo);
	return (NULL);
}

void	philo_lifecycle(t_philo *philo)
{
	while (!check_stop(philo->data))
	{
		take_forks(philo);
		philo_eat(philo);
		pthread_mutex_lock(&philo->meal_lock);
		if (philo->data->must_eat != -1
			&& philo->meals_eaten >= philo->data->must_eat)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		pthread_mutex_unlock(&philo->meal_lock);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_state(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep);
		print_state(philo, "is thinking");
		ft_sleep(1);
	}
}

void	print_state(t_philo *philo, const char *state)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	timestamp = get_time() - philo->data->start_time;
	if (!check_stop(philo->data))
	{
		printf("%s [%lld ms] Philosopher %d : ",
			philo->data->clock_emojis[philo->data->clock_index % 12],
			timestamp, philo->id);
		philo->data->clock_index++;
		if (strcmp(state, "is thinking") == 0)
			printf("🤔 Thinking...\n");
		else if (strcmp(state, "is eating") == 0)
			printf("🍽️ Enjoying a feast...\n");
		else if (strcmp(state, "is sleeping") == 0)
			printf("😴 Deeply asleep...\n");
		else if (strcmp(state, "has taken the right fork") == 0)
			printf("🍴 Has taken the right forks !\n");
		else if (strcmp(state, "has taken the left fork") == 0)
			printf("🍴 Has taken the left forks !\n");
		else if (strcmp(state, "is dead") == 0)
			printf("💀 Philosopher has died...\n");
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
