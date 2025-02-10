/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:18:19 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 15:23:43 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void	free_resources(t_table *table)
// {
// 	int	i;

// 	i = 0;
// 	if (table->forks)
// 	{
// 		while (i < table->philo_nbr)
// 		{
// 			mutex_handle(&table->forks[i].fork, DESTROY);
// 			i++;
// 		}
// 		free(table->forks);
// 		table->forks = NULL;
// 	}
// 	if (table->philos)
// 	{
// 		free(table->philos);
// 		table->philos = NULL;
// 	}
// }

void	free_resources(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork_l);
		pthread_mutex_destroy(data->philo[i].fork_r);
	}
	free(data->philo);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->dead);
}