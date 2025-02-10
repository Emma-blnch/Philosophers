/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:19:30 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 18:51:06 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_init(t_info *data)
{
	int	i;

	data->t_start = get_current_timestamp();
	i = -1;
	while (++i < data->philo_nbr)
	{
		data->philo[i].n = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].fork_r = NULL;
		data->philo[i].info = data;
		data->philo[i].meal_count = 0;
		pthread_mutex_init(&(data->philo[i].fork_l), NULL);
		if (i == data->philo_nbr - 1)
			data->philo[i].fork_r = &data->philo[0].fork_l;
		else
			data->philo[i].fork_r = &data->philo[i + 1].fork_l;
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	i = -1;
	while (++i < data->philo_nbr)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}

void	parse_input(t_info *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->limit_meals = ft_atol(argv[5]);
	else
		table->limit_meals = -1;
	if (argv[5] && table->limit_meals <= 0)
		error_exit("Limit_meals must be a positive number");
	if (table->philo_nbr > 200)
		error_exit("Too many philosophers (max 200)");
	else if (table->philo_nbr == 0)
		error_exit("There should at least be 1 philosopher");	
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		error_exit("Timestamps must be at least 60 seconds");
}

int	var_init(t_info *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		error_exit("Allocation failed for struct");
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->stop = 0;
	data->philo_eat = 0;
	return (0);
}
