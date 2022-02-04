/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:10:50 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/21 15:13:58 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	init_philo(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nb_philo)
	{
		all->philo[i].id = i;
		all->philo[i].x_ate = 0;
		all->philo[i].left_fork = i;
		all->philo[i].right_fork = (i + 1) % all->nb_philo;
		all->philo[i].last_meal = 0;
		all->philo[i].all = all;
		i++;
	}
	return (0);
}

int	init_mutex(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nb_philo)
	{
		if (pthread_mutex_init(&all->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&all->write, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&all->meal_check, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&all->died, NULL) != 0)
		return (1);
	return (0);
}

int	read_data(t_all *all)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&all->died);
	ret = all->someone_died;
	pthread_mutex_unlock(&all->died);
	return (ret);
}

int	read_ate_data(t_all *all)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&all->write);
	ret = all->philo->x_ate;
	pthread_mutex_unlock(&all->write);
	return (ret);
}
