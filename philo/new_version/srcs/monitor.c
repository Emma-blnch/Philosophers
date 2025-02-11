/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:30:19 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/11 14:41:12 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void	*check_death(void *phi)
// {
// 	t_philo	*philo;


// 	philo = (t_philo *)phi;
// 	ft_usleep(philo->info->time_to_die + 1);
// 	if(is_dead(philo, 0))
// 		return (NULL);
// 	pthread_mutex_lock(&philo->info->m_eat);
// 	pthread_mutex_lock(&philo->info->m_stop);
// 	if (!is_dead(philo, 0) && get_current_timestamp() - \
// 			philo->last_eat >= (long)(philo->info->time_to_die))
// 	{
// 		pthread_mutex_unlock(&philo->info->m_eat);
// 		pthread_mutex_unlock(&philo->info->m_stop);
// 		print(philo, R" died\n"RESET);
// 		is_dead(philo, 1);
// 	}
// 	pthread_mutex_unlock(&philo->info->m_eat);
// 	pthread_mutex_unlock(&philo->info->m_stop);
// 	return (NULL);
// }

void *check_death(void *phi)
{
    t_philo *philo;

    philo = (t_philo *)phi;
    ft_usleep(philo->info->time_to_die + 1);
    if (is_dead(philo, 0))
        return (NULL);
    mutex_handle(&philo->info->m_eat, LOCK);
    mutex_handle(&philo->info->m_stop, LOCK);
    if (!is_dead(philo, 0) && get_current_timestamp() - philo->last_eat >= (long)(philo->info->time_to_die))
    {
        mutex_handle(&philo->info->m_eat, UNLOCK);
        mutex_handle(&philo->info->m_stop, UNLOCK);
        print(philo, R" died\n"RESET);
        is_dead(philo, 1);
    }
	else
	{
		mutex_handle(&philo->info->m_eat, UNLOCK);
		mutex_handle(&philo->info->m_stop, UNLOCK);
	}
    return (NULL);
}


int is_dead(t_philo *philo, int nb)
{
	int	status;

    //pthread_mutex_lock(&philo->info->dead);
    mutex_handle(&philo->info->dead, LOCK);
    if (nb)
        philo->info->stop = 1;
    status = philo->info->stop;
   // pthread_mutex_unlock(&philo->info->dead);
    mutex_handle(&philo->info->dead, UNLOCK);
    return (status);
}
