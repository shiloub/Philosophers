/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_n_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:50:00 by amontant          #+#    #+#             */
/*   Updated: 2022/09/07 18:48:52 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	drop_forks(t_philo *philo)
{
	if (philo->index == (int)philo->all->nb_philo)
		pthread_mutex_unlock(&philo->all->forks[0]);
	else
		pthread_mutex_unlock(&philo->all->forks[philo->index]);
	usleep(100);
	pthread_mutex_unlock(&philo->all->forks[philo->index - 1]);
	usleep(100);
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mut);
	philo->last_meal = g_t(philo);
	pthread_mutex_unlock(&philo->last_meal_mut);
	pthread_mutex_lock(&philo->all->print);
	pthread_mutex_lock(&philo->all->is_dead);
	if (philo->all->dead == 1)
	{
		pthread_mutex_unlock(&philo->all->is_dead);
		pthread_mutex_unlock(&philo->all->print);
		if (philo->index == (int)philo->all->nb_philo)
			pthread_mutex_unlock(&philo->all->forks[0]);
		else
			pthread_mutex_unlock(&philo->all->forks[philo->index]);
		pthread_mutex_unlock(&philo->all->forks[philo->index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->is_dead);
	printf("%ld %d is eating\n", g_t(philo), philo->index);
	pthread_mutex_unlock(&philo->all->print);
	my_usleep(philo->all->eat * 1000, philo);
	pthread_mutex_lock(&philo->eaten_mut);
	philo->eaten++;
	pthread_mutex_unlock(&philo->eaten_mut);
	return (0);
}

int	go_to_bed(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->print);
	pthread_mutex_lock(&philo->all->is_dead);
	if (philo->all->dead == 1)
	{
		pthread_mutex_unlock(&philo->all->is_dead);
		pthread_mutex_unlock(&philo->all->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->is_dead);
	printf("%ld %d is sleeping\n", g_t(philo), philo->index);
	pthread_mutex_unlock(&philo->all->print);
	my_usleep(philo->all->sleep * 1000, philo);
	pthread_mutex_lock(&philo->all->print);
	pthread_mutex_lock(&philo->all->is_dead);
	if (philo->all->dead == 1)
	{
		pthread_mutex_unlock(&philo->all->is_dead);
		pthread_mutex_unlock(&philo->all->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->is_dead);
	printf("%ld %d is thinking\n", g_t(philo), philo->index);
	pthread_mutex_unlock(&philo->all->print);
	return (0);
}
