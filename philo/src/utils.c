/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeboose <adeboose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:07:48 by adeboose          #+#    #+#             */
/*   Updated: 2025/02/28 15:48:51 by adeboose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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

void	init_emojis(t_data *data)
{
	const char	*emojis[] = {
		"🕛", "🕐", "🕑", "🕒", "🕓", "🕔",
		"🕕", "🕖", "🕗", "🕘", "🕙", "🕚"
	};

	memcpy(data->clock_emojis, emojis, sizeof(emojis));
	data->clock_index = 0;
}
