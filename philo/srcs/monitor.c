/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:30:19 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/27 10:32:59 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	if (elapsed > philo->table->time_to_die)
	{
		set_bool(&philo->table->table_mutex,
			&philo->table->end_simulation, true);
		return (true);
	}
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
