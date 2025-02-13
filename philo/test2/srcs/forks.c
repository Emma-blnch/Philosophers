/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:15:34 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/13 14:19:35 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(char fork_name, t_phil *phil)
{
	int		*taken;
	t_fork	*fork;

	if (!is_dead(phil))
	{
		taken = &(phil->r_taken);
		fork = phil->r_fork;
		if (fork_name == 'l')
		{
			taken = &(phil->l_taken);
			fork = phil->l_fork;
		}
		pthread_mutex_lock(&(fork->lock));
		if (!(*taken) && !fork->used)
		{
			*taken = 1;
			fork->used = 1;
			pthread_mutex_unlock(&(fork->lock));
			write_state(B"has taken a fork"RESET, phil);
		}
		else
			pthread_mutex_unlock(&(fork->lock));
	}
}

void	release_fork(char fork_name, t_phil *phil)
{
	int		*taken;
	t_fork	*fork;

	taken = &(phil->r_taken);
	fork = phil->r_fork;
	if (fork_name == 'l')
	{
		taken = &(phil->l_taken);
		fork = phil->l_fork;
	}
	pthread_mutex_lock(&(fork->lock));
	*taken = 0;
	fork->used = 0;
	pthread_mutex_unlock(&(fork->lock));
}

void	release_forks_and_sleep(t_phil *phil)
{
	release_fork('r', phil);
	release_fork('l', phil);
	write_state(Y"is sleeping"RESET, phil);
	ft_usleep(phil->params->time_to_sleep);
}
