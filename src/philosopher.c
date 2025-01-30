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
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_state(philo, "is eating");
	ft_sleep(philo->data->time_to_eat);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken the left fork");
		ft_sleep(philo->data->time_to_die);
		return (NULL);
	}
	while (!check_stop(philo->data))
	{
		take_forks(philo);
		philo_eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_state(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep);
		print_state(philo, "is thinking");
	}
	return (NULL);
}
