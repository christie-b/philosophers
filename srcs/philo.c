/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:23:45 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/21 15:02:44 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	ft_init(int ac, char **av, t_all *all)
{
	if (!check_args(ac, av))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	if (parse_args(ac, av, all) == 1)
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_all	all;

	if (ft_init(ac, av, &all) == 1)
		return (1);
	all.philo = malloc(sizeof(t_philo) * all.nb_philo);
	if (!all.philo)
		return (0);
	all.forks = malloc(sizeof(pthread_mutex_t) * all.nb_philo);
	if (!all.forks)
		return (ft_free_forks(&all));
	if (init_mutex(&all) == 1)
		return (ft_free_all(&all));
	init_philo(&all);
	ft_thread_init(&all);
	if (all.forks)
		free(all.forks);
	if (all.philo)
		free(all.philo);
	return (0);
}
