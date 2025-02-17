/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:18:19 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/11 14:52:35 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_resources(t_info *table)
{
	int	i;

	i = -1;
	if (table->philo)
	{
		while (++i < table->philo_nbr)
		{
			// pthread_mutex_destroy(&table->philo[i].fork_l);
			// pthread_mutex_destroy(table->philo[i].fork_r);
			pthread_join(table->philo[i].thread, NULL);
			mutex_handle(&table->philo[i].fork_l, DESTROY);
			mutex_handle(table->philo[i].fork_r, DESTROY);
		}
		free(table->philo);
		table->philo = NULL;
	}
	// pthread_mutex_unlock(&table->print);   // Ajout
    // pthread_mutex_unlock(&table->m_stop);  // Ajout
    // pthread_mutex_unlock(&table->m_eat);   // Ajout
    // pthread_mutex_unlock(&table->dead);		// Ajout
	// pthread_mutex_destroy(&table->print);
	// pthread_mutex_destroy(&table->m_stop);
	// pthread_mutex_destroy(&table->m_eat);
	// pthread_mutex_destroy(&table->dead);
	mutex_handle(&table->print, DESTROY);
    mutex_handle(&table->m_stop, DESTROY);
    mutex_handle(&table->m_eat, DESTROY);
    mutex_handle(&table->dead, DESTROY);
}
