/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:44:58 by amontant          #+#    #+#             */
/*   Updated: 2022/09/07 19:17:26 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_all *all)
{
	int	i;

	i = 0;
	all->forks = malloc(sizeof(pthread_mutex_t) * all->nb_philo);
	while (i < (int)all->nb_philo)
	{
		pthread_mutex_init(&all->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&all->is_dead, NULL);
	pthread_mutex_init(&all->print, NULL);
}

int	main(int ac, char **av)
{
	t_philo			*philos;
	t_all			*all;
	pthread_t		monitoring;

	all = malloc(sizeof(t_all));
	all->time_start = get_actual_time();
	all->nb_eat = -1;
	all->dead = 0;
	philos = parsing(all, ac, av);
	if (!philos)
	{
		free(all);
		return (0);
	}
	set_forks(all);
	pthread_create(&monitoring, NULL, ft_monitoring, philos);
	start_routine(philos);
	join_philos(philos);
	pthread_join(monitoring, NULL);
	free(all->forks);
	free(all);
	free(philos);
	return (0);
}

void	join_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (int)philos[0].all->nb_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
