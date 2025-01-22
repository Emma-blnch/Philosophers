#include "../philo.h"

void handle_one_philo(t_table *table)
{
    t_philo *philo;
    
    philo = &table->philos[0];
    printf("%ld %d has taken a fork\n", get_current_timestamp() - table->start_simulation, philo->id);
    usleep(table->time_to_die * 1000); // Attente jusqu'à sa mort
    printf("%ld %d died\n", get_current_timestamp() - table->start_simulation, philo->id);
}

void    *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads();
    return (NULL);
}

void    dinner_start(t_table *table)
{
    int i;

    i = 0;
    if (table->philo_nbr == 1)
        return (handle_one_philo(table));
    else
    {
        while (i < table->philo_nbr)
        {
            thread_handle(&table->philo[i].thread_id, dinner_simulation, &table->philo[i], CREATE);
            i++;
        }
    }
    set_bool(&table->table_mutex, &table->all_threads_ready, true);
}
