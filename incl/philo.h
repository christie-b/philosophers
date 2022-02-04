/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:14:51 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/21 15:14:05 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <errno.h>
# include <string.h>

struct	s_all;

typedef struct s_philo
{
	int					id;
	int					x_ate;
	int					left_fork;
	int					right_fork;
	long long			last_meal;
	struct s_all		*all;
	pthread_t			thread_id;
}						t_philo;

typedef struct s_all
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_must_eat;
	int					someone_died;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		died;
	t_philo				*philo;
}						t_all;

int			check_args(int ac, char **av);
int			parse_args(int ac, char **av, t_all *all);
int			init_philo(t_all *all);
int			read_data(t_all *all);
int			read_ate_data(t_all *all);

/* THREADS */
int			init_mutex(t_all *all);
int			ft_thread_init(t_all *all);
void		ft_unlock_mutex(t_all *all, t_philo *philo);

/* ACTIONS */
int			ft_take_first_fork(t_all *all, t_philo *philo);
void		*ft_action(void *arg);
int			ft_eat(t_philo *philo);
void		check_death(t_all *all, t_philo *philo);
int			read_data(t_all *all);

/* TIME */
long long	time_elapsed(long long past, long long pres);
void		ft_usleep(long long time, t_all *all);
long long	ft_get_time(void);

/* UTILS */
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
void		print_action(t_all *all, int id, char *string);
int			ft_free_forks(t_all *all);
int			ft_free_all(t_all *all);

#endif