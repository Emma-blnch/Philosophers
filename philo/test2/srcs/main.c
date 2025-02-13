/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:15:44 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/13 15:04:05 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	free_all(t_phil*philos, t_fork *forks, int exit_code)
{
	free(philos);
	free(forks);
	return (exit_code);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_phil		*philos;
	t_fork		*forks;
	int			return_code;

	if (argc < 5 || argc > 6)
	{
		printf(R"Usage: ./philo <philo_nbr> <time_to_die> <time_to_eat> "
			"<time_to_sleep> [number_of_times_each_philosopher_must_eat]"RESET);
		return (EXIT_FAILURE);
	}
	return_code = EXIT_SUCCESS;
	if (!init_params(&params, argc, argv))
		return (EXIT_FAILURE);
	if (!create_philos(&philos, &forks, &params))
		return (EXIT_FAILURE);
	if (!create_threads(&philos, &params))
		return_code = stop_threads(&philos[0]);
	if (!wait_threads(&philos, &params))
		return (free_all(philos, forks, EXIT_FAILURE));
	return (free_all(philos, forks, return_code));
}
