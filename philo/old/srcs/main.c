/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:16:17 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/11 13:06:53 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_info	data;

	memset(&data, 0, sizeof(t_info));
	if (argc == 5 || argc == 6)
	{
		parse_input(&data, argv);
		var_init(&data);
		philo_init(&data);
		free_resources(&data);
	}
	else
		error_exit("Usage: ./philo <philo_nbr> <time_to_die> <time_to_eat> "
			"<time_to_sleep> [number_of_times_each_philosopher_must_eat]");
	return (0);
}

// check leaks
// check que si un philo meurt la simu s'arrte immédiatement
// check fermetures des threads et mutex a la fin