/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:18:19 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 18:40:52 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_resources(t_info *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->philo[i].fork_l);
		pthread_mutex_destroy(table->philo[i].fork_r);
	}
	free(table->philo);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->m_stop);
	pthread_mutex_destroy(&table->m_eat);
	pthread_mutex_destroy(&table->dead);
}
