/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:55:58 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/21 15:09:18 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	ft_free_forks(t_all *all)
{
	free(all->philo);
	all->philo = NULL;
	return (0);
}

int	ft_free_all(t_all *all)
{
	ft_putstr_fd("Mutex init failed\n", STDERR_FILENO);
	free(all->philo);
	all->philo = NULL;
	free(all->forks);
	all->forks = NULL;
	return (1);
}
