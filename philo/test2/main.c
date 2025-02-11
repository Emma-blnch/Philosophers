#include "philo.h"

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

