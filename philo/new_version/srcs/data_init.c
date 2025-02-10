/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:19:30 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 15:22:55 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// static void	fork_assign(t_philo *philo, t_fork *forks, int philo_pos)
// {
// 	int	philo_nbr;

// 	philo_nbr = philo->table->philo_nbr;
// 	if (philo->id % 2 == 0)
// 	{
// 		philo->first_fork = &forks[philo_pos];
// 		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
// 	}
// 	else
// 	{
// 		philo->second_fork = &forks[philo_pos];
// 		philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
// 	}
// }

// static void	philo_init(t_table *table)
// {
// 	int		i;
// 	t_philo	*philo;

// 	i = 0;
// 	while (i < table->philo_nbr)
// 	{
// 		philo = &table->philos[i];
// 		philo->id = i + 1;
// 		philo->meals_count = 0;
// 		philo->table = table;
// 		mutex_handle(&philo->philo_mutex, INIT);
// 		philo->last_meal_time = table->start_simulation;
// 		fork_assign(philo, table->forks, i);
// 		i++;
// 	}
// }

// void	data_init(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	table->end_simulation = false;
// 	table->all_threads_ready = false;
// 	table->threads_running_nbr = 0;
// 	table->philos = mallocation(sizeof(t_philo) * table->philo_nbr);
// 	mutex_handle(&table->table_mutex, INIT);
// 	mutex_handle(&table->write_mutex, INIT);
// 	table->forks = mallocation(sizeof(t_fork) * table->philo_nbr);
// 	while (i < table->philo_nbr)
// 	{
// 		mutex_handle(&table->forks[i].fork, INIT);
// 		table->forks[i].fork_id = i;
// 		i++;
// 	}
// 	philo_init(table);
// }

int	ft_isdigit(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
}

int	philo_init(t_info *data)
{
	int	i;

	data->t_start = timestamp();
	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].n = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].fork_r = NULL;
		data->philo[i].info = data;
		data->philo[i].m_count = 0;
		pthread_mutex_init(&(data->philo[i].fork_l), NULL);
		if (i == data->n_philo - 1)
			data->philo[i].fork_r = &data->philo[0].fork_l;
		else
			data->philo[i].fork_r = &data->philo[i + 1].fork_l;
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	i = -1;
	while (++i < data->n_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}

int	check_num(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	var_init(t_info *data, char **av)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->stop = 0;
	data->n_philo = ft_atoi(av[1]);
	if (data->n_philo <= 0)
	{
		printf("Invalid number of philosophers\n");
		return (1);
	}
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (1);
	if (check_num(av))
	{
		printf("Invalid Arguments\n");
		return (1);
	}
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->philo_eat = 0;
	if (av[5])
		data->n_eat = ft_atoi(av[5]);
	if (av[5] && data->n_eat == 0)
		return (1);
	return (0);
}