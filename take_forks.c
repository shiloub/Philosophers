/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:24:57 by amontant          #+#    #+#             */
/*   Updated: 2022/09/07 18:48:31 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_first_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->forks[philo->index - 1]);
	pthread_mutex_lock(&philo->all->print);
	pthread_mutex_lock(&philo->all->is_dead);
	if (philo->all->dead == 1)
	{
		pthread_mutex_unlock(&philo->all->is_dead);
		pthread_mutex_unlock(&philo->all->print);
		pthread_mutex_unlock(&philo->all->forks[philo->index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->is_dead);
	printf("%ld %d has taken a fork\n", g_t(philo), philo->index);
	pthread_mutex_unlock(&philo->all->print);
	return (0);
}

int	take_fork_for_last(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->forks[0]);
	pthread_mutex_lock(&philo->all->print);
	pthread_mutex_lock(&philo->all->is_dead);
	if (philo->all->dead == 1)
	{
		pthread_mutex_unlock(&philo->all->is_dead);
		pthread_mutex_unlock(&philo->all->print);
		pthread_mutex_unlock(&philo->all->forks[0]);
		pthread_mutex_unlock(&philo->all->forks[philo->index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->is_dead);
	printf("%ld %d has taken a fork\n", g_t(philo), philo->index);
	pthread_mutex_unlock(&philo->all->print);
	return (0);
}

int	take_second_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->forks[philo->index]);
	pthread_mutex_lock(&philo->all->print);
	pthread_mutex_lock(&philo->all->is_dead);
	if (philo->all->dead == 1)
	{
		pthread_mutex_unlock(&philo->all->is_dead);
		pthread_mutex_unlock(&philo->all->print);
		pthread_mutex_unlock(&philo->all->forks[philo->index]);
		pthread_mutex_unlock(&philo->all->forks[philo->index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->is_dead);
	printf("%ld %d has taken a fork\n", g_t(philo), philo->index);
	pthread_mutex_unlock(&philo->all->print);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (take_first_fork(philo) == 1)
		return (1);
	if (philo->index == (int)philo->all->nb_philo)
	{
		if (take_fork_for_last(philo) == 1)
			return (1);
	}
	else
	{
		if (take_second_fork(philo) == 1)
			return (1);
	}
	return (0);
}
