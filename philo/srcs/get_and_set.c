/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:29:14 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/27 10:30:06 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	result;

	mutex_handle(mutex, LOCK);
	result = *value;
	mutex_handle(mutex, UNLOCK);
	return (result);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	result;

	mutex_handle(mutex, LOCK);
	result = *value;
	mutex_handle(mutex, UNLOCK);
	return (result);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
