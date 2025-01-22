#include "../philo.h"

void    free_resources(t_table *table)
{
    int i;

    i = 0;
    if (table->forks)
    {
        while (i < table->philo_nbr)
        {
            mutex_handle(&table->forks[i].fork, DESTROY);
            i++;
        }
        free(table->forks);
        table->forks = NULL;
    }
    if (table->philos)
    {
        free(table->philos);
        table->philos = NULL;
    }
}
