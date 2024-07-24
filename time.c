/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:00:09 by shiloub           #+#    #+#             */
/*   Updated: 2022/09/07 18:09:51 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	do_i_die(t_philo *philo)
{
	if (g_t(philo) - philo->last_meal > philo->all->die)
		return (1);
	return (0);
}

unsigned long	g_t(t_philo *philo)
{
	return (get_actual_time() - philo->all->time_start);
}

void	my_usleep(unsigned long usec, t_philo *philo)
{
	unsigned long	time_start;
	unsigned long	time_actual;
	struct timeval	time;

	gettimeofday(&time, NULL);
	time_start = (time.tv_sec * 1000000) + (time.tv_usec);
	time_actual = time_start;
	while (time_actual < time_start + usec)
	{
		usleep(500);
		gettimeofday(&time, NULL);
		time_actual = (time.tv_sec * 1000000) + (time.tv_usec);
		if (philo != NULL)
		{
			pthread_mutex_lock(&philo->all->is_dead);
			if (philo->all->dead == 1)
			{
				pthread_mutex_unlock(&philo->all->is_dead);
				break ;
			}
			pthread_mutex_unlock(&philo->all->is_dead);
		}
	}
}
