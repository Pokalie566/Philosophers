/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeboose <adeboose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:07:48 by adeboose          #+#    #+#             */
/*   Updated: 2025/02/05 08:07:49 by adeboose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, const char *state)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	timestamp = get_time() - philo->data->start_time;
	if (!check_stop(philo->data))
	{
		printf("⌛ [%lld ms] Philosopher %d : ", timestamp, philo->id);
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
		printf("===========================================\n");
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_sleep(long long ms)
{
	long long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

int	check_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_lock);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_lock);
	return (stop);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}
