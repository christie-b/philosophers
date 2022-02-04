/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:47:38 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/21 15:14:08 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	ft_usleep(long long time_to_sleep, t_all *all)
{
	long long	i;

	i = ft_get_time();
	while (read_data(all) == 0)
	{
		if (time_elapsed(i, ft_get_time()) >= time_to_sleep)
			break ;
		usleep(50);
	}
}

long long	time_elapsed(long long past, long long pres)
{
	return (pres - past);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
