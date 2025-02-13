/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:15:38 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/13 15:19:20 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philo(t_phil *phil, t_fork **forks, t_params *params, int cur)
{
	phil->params = params;
	phil->pos = cur;
	phil->last_meal = 0;
	phil->meal_count = 0;
	phil->r_fork = &((*forks)[cur]);
	phil->r_taken = 0;
	phil->l_taken = 0;
	if (cur == params->num - 1)
		phil->l_fork = &((*forks)[0]);
	else
		phil->l_fork = &((*forks)[cur + 1]);
	phil->l_fork->used = 0;
	pthread_mutex_init(&(phil->m_last_meal), NULL);
	pthread_mutex_init(&(phil->l_fork->lock), NULL);
}

int	create_philos(t_phil **philos, t_fork **forks, t_params	*params)
{
	int	cur;

	*philos = malloc(sizeof(t_phil) * params->num);
	if (!(*philos))
		return (0);
	*forks = malloc(sizeof(t_fork) * params->num);
	if (!(*forks))
	{
		free(*philos);
		return (0);
	}
	cur = 0;
	while (cur < params->num)
	{
		init_philo(&(*philos)[cur], forks, params, cur);
		cur++;
	}
	return (1);
}

int	init_params(t_params *params, int argc, char **argv)
{
	params->num = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->meal_max = -1;
	if (argc == 6)
	{
		params->meal_max = ft_atoi(argv[5]);
		if (ft_atoi(argv[5]) < 0)
			return (0);
	}
	params->is_dead = 0;
	if (params->num <= 0 || params->num > 200
		|| params->time_to_die < 60 || params->time_to_eat < 60
		|| params->time_to_sleep < 60)
		return (printf(R"Minimum 60 seconds for"
				" each time and 200 philosophers max"RESET), 0);
	pthread_mutex_init(&(params->console_mutex), NULL);
	pthread_mutex_init(&(params->m_is_dead), NULL);
	return (1);
}
