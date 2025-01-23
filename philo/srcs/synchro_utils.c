#include "../philo.h"

// Increase number of threads running to synchro with monitor
void    increase_long(t_mtx *mutex, long *value)
{
    mutex_handle(mutex, LOCK);
    (*value)++;
    mutex_handle(mutex, UNLOCK);
}

// Monitor busy waits until threads are not running
bool    all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool    ret;

    ret = false;
    mutex_handle(mutex, LOCK);
    if (*threads == philo_nbr)
        ret = true;
    mutex_handle(mutex, UNLOCK);
    return (ret);
}

// Spinlock to synchro philos start
void	wait_all_threads(t_table *table)
{
    while (!get_bool(&table->table_mutex, &table->all_threads_ready))
        ;
}

// More precise usleep than the original
// void    precise_usleep(long usec, t_table *table)
// {
//     long    start;
//     long    elapsed;
//     long    remaining;

//     start = get_time(MICROSECOND);
//     while (get_time(MICROSECOND) - start < usec)
//     {
//         if (simulation_finished(table))
//             break ;
//         elapsed = get_time(MICROSECOND) - start;
//         remaining = usec - elapsed;
//         if (remaining > 1e3)
//             usleep (usec / 2);
//         else
//         {
//             while (get_time(MICROSECOND) - start < usec)
//                 ;
//         }
//     }
// }

void precise_usleep(long usec, t_table *table)
{
    long start;
    long elapsed;

    start = get_time(MICROSECOND);
    while (1)
    {
        elapsed = get_time(MICROSECOND) - start;
        if (elapsed >= usec || simulation_finished(table))
            break;
        if (usec - elapsed > 1000)
            usleep((usec - elapsed) / 2);
    }
}

// Print the status messages
void    write_status(t_status status, t_philo *philo)
{
    long    elapsed;

    elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
    mutex_handle(&philo->table->write_mutex, LOCK);
    if (status == DIED)
        printf(R"%-6ld %d died\n"RESET, elapsed, philo->id);
    else if (!simulation_finished(philo->table))
    {
        if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
            printf(W"%-6ld"B"%d has taken a fork\n"RESET, elapsed, philo->id);
        else if (status == EATING)
            printf(W"%-6ld"G"%d is eating\n"RESET, elapsed, philo->id);
        else if (status == SLEEPING)
            printf(W"%-6ld"Y"%d is sleeping\n"RESET, elapsed, philo->id);
        else if (status == THINKING)
            printf(W"%-6ld"M"%d is thinking\n"RESET, elapsed, philo->id);
    }
    mutex_handle(&philo->table->write_mutex, UNLOCK);
}
