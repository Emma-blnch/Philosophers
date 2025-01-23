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

// long	get_current_timestamp(void)
// {
//     struct timeval tv;

//     gettimeofday(&tv, NULL);
//     return (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
// }

long    get_time(t_time_code timecode)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        error_exit("gettimeofday failed");
    if (timecode == SECOND)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if (timecode == MILLISECOND)
        return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (timecode == MICROSECOND)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("Wrong input to get_time");
    return (1337);
}
