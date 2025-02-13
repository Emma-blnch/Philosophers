/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:15:29 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/13 15:29:10 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_dead(t_phil *phil)
{
	int	alive;

	pthread_mutex_lock(&(phil->params->m_is_dead));
	alive = phil->params->is_dead;
	pthread_mutex_unlock(&(phil->params->m_is_dead));
	return (alive);
}

int	stop_threads(t_phil *phil)
{
	pthread_mutex_lock(&(phil->params->m_is_dead));
	phil->params->is_dead = 1;
	pthread_mutex_unlock(&(phil->params->m_is_dead));
	return (EXIT_FAILURE);
}

int	check_philo_death(t_phil *phil, long cur_time)
{
	int	dead;
	int	last_meal;

	dead = 0;
	pthread_mutex_lock(&(phil->m_last_meal));
	last_meal = cur_time - phil->last_meal;
	pthread_mutex_unlock(&(phil->m_last_meal));
	if (last_meal > phil->params->time_to_die)
	{
		pthread_mutex_lock(&(phil->params->console_mutex));
		pthread_mutex_lock(&(phil->params->m_is_dead));
		phil->params->is_dead = 1;
		pthread_mutex_unlock(&(phil->params->m_is_dead));
		printf(R"%03ld %d died\n"RESET, cur_time, phil->pos);
		pthread_mutex_unlock(&(phil->params->console_mutex));
		dead = 1;
	}
	return (dead);
}

// void	*check_philos_death(void *arg)
// {
// 	t_params	*params;
// 	t_phil		**philos;
// 	long		cur_time;
// 	int			cur;

// 	philos = (t_phil **)arg;
// 	params = philos[0]->params;
// 	while (1)
// 	{
// 		cur = 0;
// 		cur_time = get_timestamp() - params->start_time;
// 		while (cur < params->num)
// 		{
// 			if (check_philo_death(&(*philos)[cur], cur_time))
// 				return (NULL);
// 			cur++;
// 		}
// 		ft_usleep(1);
// 	}
// 	return (NULL);
// }

void	*check_philos_death(void *arg)
{
	t_params	*params;
	t_phil		**philos;
	long		cur_time;
	int			cur;
	int			finished_eating;

	philos = (t_phil **)arg;
	params = philos[0]->params;
	while (1)
	{
		cur = 0;
		finished_eating = 1;
		cur_time = get_timestamp() - params->start_time;
		while (cur < params->num)
		{
			if (check_philo_death(&(*philos)[cur], cur_time))
				return (NULL);
			pthread_mutex_lock(&((*philos)[cur].m_last_meal));
			if (params->meal_max > 0 && (*philos)[cur].meal_count < params->meal_max)
				finished_eating = 0;
			pthread_mutex_unlock(&((*philos)[cur].m_last_meal));
			
			cur++;
		}
		if (params->meal_max > 0 && finished_eating)
		{
			pthread_mutex_lock(&(params->m_is_dead));
			params->is_dead = 1;
			pthread_mutex_unlock(&(params->m_is_dead));
			return (NULL);
		}

		ft_usleep(1);
	}
	return (NULL);
}
