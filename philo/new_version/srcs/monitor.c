/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:30:19 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 18:58:21 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*check_death(void *phi)
{
	t_philo	*philo;


	philo = (t_philo *)phi;
	ft_usleep(philo->info->time_to_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);
	if (!is_dead(philo, 0) && get_current_timestamp() - \
			philo->last_eat >= (long)(philo->info->time_to_die))
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
		print(philo, R" died\n"RESET);
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_stop);
	return (NULL);
}

// int	is_dead(t_philo *philo, int nb)
// {
// 	pthread_mutex_lock(&philo->info->dead);
// 	if (nb)
// 		philo->info->stop = 1;
// 	if (philo->info->stop)
// 	{
// 		pthread_mutex_unlock(&philo->info->dead);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->info->dead);
// 	return (0);
// }

int is_dead(t_philo *philo, int nb)
{
    pthread_mutex_lock(&philo->info->dead);
    if (nb)
    {
        philo->info->stop = 1;
        pthread_mutex_unlock(&philo->info->dead);
        return (1);
    }
    int status = philo->info->stop;
    pthread_mutex_unlock(&philo->info->dead);
    return status;
}
