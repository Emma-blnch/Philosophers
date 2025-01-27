/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:16:17 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/27 10:43:56 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		free_resources(&table);
	}
	else
		error_exit("Usage: ./philo <philo_nbr> <time_to_die> <time_to_eat> "
			"<time_to_sleep> [number_of_times_each_philosopher_must_eat]");
	return (0);
}

//printf("\n[DEBUG] Philosopher meals:\n");
//for (int i = 0; i < table.philo_nbr; i++)
//{
//	printf("Philosopher %d: %ld meals\n",
//		table.philos[i].id, table.philos[i].meals_count);
//}
