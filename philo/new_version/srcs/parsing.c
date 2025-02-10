/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:33:08 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/27 10:35:06 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	convert_to_ms(t_table *table, long time_to_die,
		long time_to_eat, long time_to_sleep)
{
	if (time_to_die > LONG_MAX / 1000 || time_to_eat > LONG_MAX / 1000
		|| time_to_sleep > LONG_MAX / 1000)
		error_exit("Time value too large after conversion to milliseconds");
	table->time_to_die = time_to_die * 1000;
	table->time_to_eat = time_to_eat * 1000;
	table->time_to_sleep = time_to_sleep * 1000;
}

static void	check_numbers(t_table *table, char **argv)
{
	if (argv[5] && table->limit_meals <= 0)
		error_exit("Limit_meals must be a positive number");
	if (table->philo_nbr > 200)
		error_exit("Too many philosophers (max 200)");
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		error_exit("Timestamps must be at least 60 seconds");
}

void	parse_input(t_table *table, char **argv)
{
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;

	table->philo_nbr = ft_atol(argv[1]);
	time_to_die = ft_atol(argv[2]);
	time_to_eat = ft_atol(argv[3]);
	time_to_sleep = ft_atol(argv[4]);
	convert_to_ms(table, time_to_die, time_to_eat, time_to_sleep);
	if (argv[5])
		table->limit_meals = ft_atol(argv[5]);
	else
		table->limit_meals = -1;
	check_numbers(table, argv);
}
