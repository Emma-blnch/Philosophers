/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:18:19 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/27 10:19:18 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_resources(t_table *table)
{
	int	i;

	i = 0;
	if (table->forks)
	{
		while (i < table->philo_nbr)
		{
			mutex_handle(&table->forks[i].fork, DESTROY);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}
