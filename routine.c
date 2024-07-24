/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:54:50 by amontant          #+#    #+#             */
/*   Updated: 2022/09/07 18:49:31 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_real(t_philo *philo)
{
	if (philo->all->nb_philo == 1)
	{
		printf("%ld %d has taken a fork\n", g_t(philo), philo->index);
		my_usleep(philo->all->die * 2000, philo);
		return ;
	}
	while (1)
	{
		if (take_forks(philo) == 1)
			break ;
		if (eat(philo) == 1)
			break ;
		if (drop_forks(philo) == 1)
			break ;
		if (go_to_bed(philo) == 1)
			break ;
	}
}

void	*routine(void *arg)
{
	routine_real(arg);
	return (NULL);
}

void	start_routine(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (int)philos[0].all->nb_philo)
	{	
		if (philos[i].index % 2 == 0)
			pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	my_usleep(10000, NULL);
	i = 0;
	while (i < (int)philos[0].all->nb_philo)
	{	
		if (philos[i].index % 2 == 1)
			pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
}
