/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:19:30 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/27 10:22:50 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	fork_assign(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
	else
	{
		philo->second_fork = &forks[philo_pos];
		philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->meals_count = 0;
		philo->table = table;
		mutex_handle(&philo->philo_mutex, INIT);
		philo->last_meal_time = table->start_simulation;
		fork_assign(philo, table->forks, i);
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	table->philos = mallocation(sizeof(t_philo) * table->philo_nbr);
	mutex_handle(&table->table_mutex, INIT);
	mutex_handle(&table->write_mutex, INIT);
	table->forks = mallocation(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
}
