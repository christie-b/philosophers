/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:12:03 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/21 15:34:44 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	ft_check_death(t_all *all, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < all->nb_philo && read_data(all) == 0)
	{
		pthread_mutex_lock(&(all->meal_check));
		if (time_elapsed(philo[i].last_meal, ft_get_time())
			> all->time_to_die)
		{
			pthread_mutex_lock(&all->died);
			print_action(all, i, "died");
			all->someone_died = 1;
			pthread_mutex_unlock(&all->died);
		}
		pthread_mutex_unlock(&(all->meal_check));
		usleep(100);
		i++;
	}
}

void	check_death(t_all *all, t_philo *philo)
{
	int	i;

	while (all->all_ate == 0)
	{
		ft_check_death(all, philo);
		if (all->someone_died == 1)
			break ;
		i = 0;
		while (all->nb_must_eat != -1 && i < all->nb_philo
			&& read_ate_data(all) >= all->nb_must_eat)
			i++;
		if (i == all->nb_philo)
		{
			pthread_mutex_lock(&all->write);
			all->all_ate = 1;
			pthread_mutex_unlock(&all->write);
		}
	}
}

int	ft_join_and_destroy(t_all *all, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < all->nb_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
		{
			ft_putstr_fd("pthread_join failed\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < all->nb_philo)
	{
		if (pthread_mutex_destroy(&(all->forks[i])) != 0)
		{
			ft_putstr_fd("Mutex destroy failed\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	pthread_mutex_destroy(&(all->write));
	return (0);
}

int	ft_thread_init(t_all *all)
{
	int		i;
	t_philo	*philo;

	philo = all->philo;
	i = 0;
	all->first_timestamp = ft_get_time();
	while (i < all->nb_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL,
				ft_action, &philo[i]) != 0)
		{
			ft_putstr_fd("Failed to create thread\n", STDERR_FILENO);
			return (1);
		}
		pthread_mutex_lock(&all->write);
		philo[i].last_meal = ft_get_time();
		pthread_mutex_unlock(&all->write);
		i++;
	}
	check_death(all, all->philo);
	if (ft_join_and_destroy(all, philo) == 1)
		return (1);
	return (0);
}
