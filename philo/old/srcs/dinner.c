/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:22:59 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/11 14:58:47 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_philo *philo)
{
	//pthread_mutex_lock(&(philo->fork_l));
	mutex_handle(&(philo->fork_l), LOCK);
	print(philo, B" has taken a fork\n"RESET);
	if (philo->info->philo_nbr == 1)
	{
		ft_usleep(philo->info->time_to_die * 2);
		mutex_handle(&(philo->fork_l), UNLOCK);
		return ;
	}
	//pthread_mutex_lock((philo->fork_r));
	mutex_handle((philo->fork_r), LOCK);
	print(philo, B" has taken a fork\n"RESET);
}

// void	philo_eat(t_philo *philo)
// {
// 	print(philo, G" is eating\n"RESET);
// 	pthread_mutex_lock(&(philo->info->m_eat));
// 	philo->last_eat = get_current_timestamp();
// 	philo->meal_count++;
// 	pthread_mutex_unlock(&(philo->info->m_eat));
// 	ft_usleep(philo->info->time_to_eat);
// 	pthread_mutex_unlock((philo->fork_r));
// 	pthread_mutex_unlock(&(philo->fork_l));
// 	print(philo, Y" is sleeping\n"RESET);
// 	ft_usleep(philo->info->time_to_sleep);
// 	print(philo, M" is thinking\n"RESET);
// }

void philo_eat(t_philo *philo)
{
    print(philo, G" is eating\n"RESET);
    mutex_handle(&(philo->info->m_eat), LOCK);
    philo->last_eat = get_current_timestamp();
    philo->meal_count++;
    mutex_handle(&(philo->info->m_eat), UNLOCK);
    ft_usleep(philo->info->time_to_eat);
	if (philo->fork_r)
    	mutex_handle(philo->fork_r, UNLOCK);
	if (philo->info->philo_nbr > 1)
    	mutex_handle(&(philo->fork_l), UNLOCK);
    print(philo, Y" is sleeping\n"RESET);
    ft_usleep(philo->info->time_to_sleep);
    print(philo, M" is thinking\n"RESET);
}

void *philo_life(void *phi)
{
    t_philo *philo;
    //pthread_t t;

    philo = (t_philo *)phi;
    if (philo->n % 2 == 0)
        ft_usleep(philo->info->time_to_eat / 10);
    while (!is_dead(philo, 0))
    {
        thread_handle(&philo->thread, check_death, phi, CREATE);
        take_fork(philo);
        philo_eat(philo);
		if (is_dead(philo, 0)) return (NULL);
        //thread_handle(&t, NULL, NULL, DETACH);
		pthread_join(philo->thread, NULL);
        if (philo->meal_count == philo->info->limit_meals)
        {
            mutex_handle(&philo->info->m_stop, LOCK);
            if (++philo->info->philo_eat == philo->info->philo_nbr)
            {
                mutex_handle(&philo->info->m_stop, UNLOCK);
                is_dead(philo, 2);
            }
            mutex_handle(&philo->info->m_stop, UNLOCK);
            return (NULL);
        }
    }
    return (NULL);
}

// void	*philo_life(void *phi)
// {
// 	t_philo		*philo;
// 	pthread_t	t;

// 	philo = (t_philo *)phi;
// 	if (philo->n % 2 == 0)
// 		ft_usleep(philo->info->time_to_eat / 10);
// 	while (!is_dead(philo, 0))
// 	{
// 		pthread_create(&t, NULL, check_death, phi);
// 		take_fork(philo);
// 		philo_eat(philo);
// 		pthread_detach(t);
// 		if (is_dead(philo, 0)) //add
//             return (NULL);//add
// 		if (philo->meal_count == philo->info->limit_meals)
// 		{
// 			pthread_mutex_lock(&philo->info->m_stop);
// 			if (++philo->info->philo_eat == philo->info->philo_nbr)
// 			{
// 				pthread_mutex_unlock(&philo->info->m_stop);
// 				is_dead(philo, 2);
// 			}
// 			pthread_mutex_unlock(&philo->info->m_stop);
// 			return (NULL);
// 		}
// 	}
// 	return (NULL);
// }