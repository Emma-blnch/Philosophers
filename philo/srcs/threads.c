/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:15:49 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/17 09:18:33 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_threads(t_phil **philos, t_params *params)
{
	int	cur;

	params->start_time = get_timestamp();
	cur = 0;
	while (cur < params->num)
	{
		if (pthread_create(&((*philos)[cur].thread), NULL,
			philo_life, &((*philos)[cur])))
			return (0);
		cur++;
	}
	if (pthread_create(&(params->death_thread), NULL,
			check_philos_death, philos))
		return (0);
	return (1);
}

int	wait_threads(t_phil **philos, t_params *params)
{
	int	cur;
	int	return_code;

	cur = 0;
	return_code = 1;
	while (cur < params->num)
	{
		if (pthread_join((*philos)[cur].thread, NULL))
			return_code = 0;
		cur++;
	}
	if (pthread_join(params->death_thread, NULL))
		return_code = 0;
	return (return_code);
}

void	philo_eat(t_phil *phil)
{
	write_state(G"is eating"RESET, phil);
	ft_usleep(phil->params->time_to_eat);
	pthread_mutex_lock(&(phil->m_last_meal));
	phil->meal_count++;
	phil->last_meal = get_timestamp() - phil->params->start_time;
	pthread_mutex_unlock(&(phil->m_last_meal));
	release_forks_and_sleep(phil);
}

void	*philo_life(void *arg)
{
	t_phil		*phil;

	phil = (t_phil *)arg;
	if (phil->pos % 2 != 0)
		ft_usleep(phil->params->time_to_eat + (phil->pos * 5) % 10);
	while (!is_dead(phil))
	{
		if (phil->meal_count >= phil->params->meal_max
			&& phil->params->meal_max > 0)
			break ;
		take_fork('l', phil);
		if (phil->l_taken)
			take_fork('r', phil);
		if (phil->r_taken && phil->l_taken)
		{
			philo_eat(phil);
			thinking_state(phil);
		}
	}
	pthread_exit(NULL);
}

// void	*philo_life(void *arg)
// {
// 	t_phil		*phil;

// 	phil = (t_phil *)arg;
// 	if (phil->pos % 2 != 0)
// 		ft_usleep(phil->params->time_to_eat);
// 	while (!is_dead(phil))
// 	{
// 		// if (phil->params->meal_max > 0)
// 		// {
// 		// 	pthread_mutex_lock(&(phil->m_last_meal));
// 		// 	if (phil->meal_count >= phil->params->meal_max)
// 		// 	{
// 		// 		pthread_mutex_unlock(&(phil->m_last_meal));
// 		// 		break ;
// 		// 	}
// 		// 	pthread_mutex_unlock(&(phil->m_last_meal));
// 		// }
// 		if (phil->meal_count >= phil->params->meal_max
// 			&& phil->params->meal_max > 0)
// 			break ;
// 		take_fork('l', phil);
// 		if (phil->l_taken)
// 			take_fork('r', phil);
// 		if (phil->r_taken && phil->l_taken)
// 		{
// 			write_state(G"is eating"RESET, phil);
// 			ft_usleep(phil->params->time_to_eat);
// 			pthread_mutex_lock(&(phil->m_last_meal));
// 			phil->meal_count++;
// 			phil->last_meal = get_timestamp() - phil->params->start_time;
// 			pthread_mutex_unlock(&(phil->m_last_meal));
// 			release_forks_and_sleep(phil);
// 			thinking_state(phil);
// 		}
// 	}
// 	pthread_exit(NULL);
// }

//ft_usleep(phil->params->time_to_eat);