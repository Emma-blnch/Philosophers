/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:07:34 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/17 09:19:06 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_is_dead(t_params *params)
{
	pthread_mutex_lock(&(params->m_is_dead));
	params->is_dead = 1;
	pthread_mutex_unlock(&(params->m_is_dead));
}

void	thinking_state(t_phil *phil)
{
	write_state(M"is thinking"RESET, phil);
	ft_usleep(10);
}
