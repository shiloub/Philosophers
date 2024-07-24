/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:00:57 by amontant          #+#    #+#             */
/*   Updated: 2022/09/07 19:05:40 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos[i].last_meal_mut);
	if (do_i_die(&philos[i]) == 1)
	{
		pthread_mutex_unlock(&philos[i].last_meal_mut);
		pthread_mutex_lock(&philos->all->is_dead);
		philos->all->dead = 1;
		pthread_mutex_unlock(&philos->all->is_dead);
		pthread_mutex_lock(&philos->all->print);
		printf("%ld %d died\n", g_t(philos), i + 1);
		pthread_mutex_unlock(&philos->all->print);
		return (1);
	}
	pthread_mutex_unlock(&philos[i].last_meal_mut);
	return (0);
}

int	check_count(t_philo *philos, int i, int count)
{
	if (count == (int)philos[i].all->nb_philo)
	{
		pthread_mutex_lock(&philos->all->is_dead);
		philos->all->dead = 1;
		pthread_mutex_unlock(&philos->all->is_dead);
		return (1);
	}
	return (0);
}

void	ft_monitoring_real(t_philo *philos)
{
	int	i;
	int	count;

	count = 0;
	while (1)
	{
		i = 0;
		while (i < (int)philos[0].all->nb_philo)
		{
			if (die(philos, i) == 1)
				return ;
			pthread_mutex_lock(&philos[i].eaten_mut);
			if (philos[i].eaten == (int)philos[i].all->nb_eat \
				&& philos[i].all_eat == 0)
			{
				philos[i].all_eat = 1;
				count++;
			}
			pthread_mutex_unlock(&philos[i].eaten_mut);
			if (check_count(philos, i, count) == 1)
				return ;
			i++;
		}
	}
}

void	*ft_monitoring(void *arg)
{
	ft_monitoring_real(arg);
	return (NULL);
}
