/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:23:54 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/16 15:08:46 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_is_nbr(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (0);
	else
	{
		i = 1;
		while (i < 5)
		{
			if (!(*av[i]))
				return (0);
			if (!ft_is_nbr(av[i]))
				return (0);
			i++;
		}
	}
	if (ac == 6 && !*av[5])
		return (0);
	return (1);
}

int	parse_args(int ac, char **av, t_all *all)
{
	all->nb_philo = ft_atoi(av[1]);
	all->time_to_die = ft_atoi(av[2]);
	all->time_to_eat = ft_atoi(av[3]);
	all->time_to_sleep = ft_atoi(av[4]);
	all->nb_must_eat = -1;
	if (ac == 6)
		all->nb_must_eat = ft_atoi(av[5]);
	if (all->nb_philo < 0 || all->time_to_die < 0
		|| all->time_to_eat < 0 || all->time_to_sleep < 0)
		return (1);
	all->all_ate = 0;
	all->someone_died = 0;
	return (0);
}
