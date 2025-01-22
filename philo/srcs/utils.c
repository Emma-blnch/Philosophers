#include "../philo.h"

void	error_exit(const char *error)
{
	printf(R"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}

void	*mallocation(size_t bytes)
{
	void	*result;
	
	result = malloc(bytes);
	if (result == NULL)
		error_exit("Malloc failed");
	return (result);
}

void wait_for_threads_and_clean(t_table *table, pthread_t supervisor)
{
	int	i;

	i = 0;
    while (i < table->philo_nbr)
    {
        thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
    }
    thread_handle(&supervisor, NULL, NULL, JOIN);
    free_resources(table);
}

long	ft_atol(const char *string)
{
	long	result;
	size_t	index;

	index = 0;
	result = 0;
	while (string[index] == ' ' || (string[index] >= 9 && string[index] <= 13))
		index++;
	if (string[index] == '+')
		index++;
    else if (string[index] == '-')
        error_exit("Only positive values allowed");
	while (string[index] >= '0' && string[index] <= '9')
	{
		if (result > (LONG_MAX - (string[index] - '0')) / 10)
            error_exit("Number too large");
		result = result * 10 + (string[index] - '0');
		index++;
	}
	while (string[index] == ' ' || (string[index] >= 9 && string[index] <= 13))
		index++;
    if (string[index] != '\0')
        error_exit("Invalid characters in input");
	return (result);
}
