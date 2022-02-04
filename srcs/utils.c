/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:24:25 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/21 15:14:18 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	print_action(t_all *all, int id, char *str)
{
	pthread_mutex_lock(&(all->write));
	if (all->someone_died == 0)
		printf("%lld %d %s\n", ft_get_time() - all->first_timestamp,
			id + 1, str);
	pthread_mutex_unlock(&(all->write));
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	result;
	int					sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
		else if (result > 9223372036854775807 && sign == -1)
			return (0);
	}
	return (sign * result);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
