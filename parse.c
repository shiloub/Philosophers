/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:19:13 by amontant          #+#    #+#             */
/*   Updated: 2022/09/07 18:47:12 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		printf("wrong number of arguments\n");
		exit (0);
	}
	while (i < ac)
	{
		if (!check_numbers(av[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	check_numbers(char *number)
{
	int	i;

	i = 0;
	while (number[i])
	{
		if (number[i] < '0' || number[i] > '9')
		{
			printf("arg isnt valid\n");
			exit(0);
		}
		i++;
	}
	return (1);
}

int	parse_args(t_all *all, int ac, char **av)
{
	all->nb_eat = -1;
	if (check_arg(ac, av) != 0)
		return (1);
	all->nb_philo = ft_atoi(av[1]);
	all->die = ft_atoi(av[2]);
	all->eat = ft_atoi(av[3]);
	all->sleep = ft_atoi(av[4]);
	if (ac == 6)
		all->nb_eat = ft_atoi(av[5]);
	if (all->nb_philo == 0 || all->die <= 0 || all->eat <= 0 || \
		all->sleep <= 0 || all->nb_eat <= 0)
		return (1);
	return (0);
}

t_philo	*parsing(t_all *all, int ac, char **av)
{
	int		i;
	t_philo	*philos;

	if (parse_args(all, ac, av) == 1)
		return (0);
	i = 0;
	philos = malloc(sizeof(t_philo) * all->nb_philo);
	while (i < (int)all->nb_philo)
	{
		philos[i].index = i + 1;
		philos[i].all = all;
		philos[i].all_eat = 0;
		philos[i].eaten = 0;
		philos[i].is_eating = 0;
		philos[i].last_meal = 0;
		pthread_mutex_init(&philos[i].is_eating_mut, NULL);
		pthread_mutex_init(&philos[i].last_meal_mut, NULL);
		pthread_mutex_init(&philos[i].eaten_mut, NULL);
		i++;
	}
	return (philos);
}
