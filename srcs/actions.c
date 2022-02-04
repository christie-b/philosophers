/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:04:27 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/21 15:20:16 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	ft_take_first_fork(t_all *all, t_philo *philo)
{
	if (philo->id == all->nb_philo - 1)
		pthread_mutex_lock(&(all->forks[philo->right_fork]));
	else
		pthread_mutex_lock(&(all->forks[philo->left_fork]));
	print_action(all, philo->id, "has taken a fork");
	if (all->nb_philo == 1)
	{
		if (philo->id == all->nb_philo - 1)
		{
			pthread_mutex_unlock(&(all->forks[philo->right_fork]));
		}
		else
			pthread_mutex_unlock(&(all->forks[philo->left_fork]));
		return (1);
	}
	if (philo->id == all->nb_philo - 1)
		pthread_mutex_lock(&(all->forks[philo->left_fork]));
	else
		pthread_mutex_lock(&(all->forks[philo->right_fork]));
	print_action(all, philo->id, "has taken a fork");
	return (0);
}

void	ft_unlock_mutex(t_all *all, t_philo *philo)
{
	pthread_mutex_unlock(&all->write);
	if (philo->id == all->nb_philo - 1)
	{
		pthread_mutex_unlock(&(all->forks[philo->right_fork]));
		pthread_mutex_unlock(&(all->forks[philo->left_fork]));
	}
	else
	{
		pthread_mutex_unlock(&(all->forks[philo->left_fork]));
		pthread_mutex_unlock(&(all->forks[philo->right_fork]));
	}
}

int	ft_eat(t_philo *philo)
{
	t_all	*all;

	all = philo->all;
	if (ft_take_first_fork(all, philo) == 1)
		return (1);
	pthread_mutex_lock(&(all->meal_check));
	print_action(all, philo->id, "is eating");
	pthread_mutex_lock(&all->write);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&all->write);
	pthread_mutex_unlock(&(all->meal_check));
	ft_usleep(all->time_to_eat, all);
	pthread_mutex_lock(&all->write);
	(philo->x_ate)++;
	ft_unlock_mutex(all, philo);
	return (0);
}

void	*ft_action(void *arg)
{
	int			i;
	t_philo		*philo;
	t_all		*all;

	i = 0;
	philo = (t_philo *)arg;
	all = philo->all;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (read_data(all) == 0)
	{
		if (all->nb_must_eat == 0)
			break ;
		if (ft_eat(philo) == 1)
			break ;
		if (all->all_ate == 1)
			break ;
		print_action(all, philo->id, "is sleeping");
		ft_usleep(all->time_to_sleep, all);
		print_action(all, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}
