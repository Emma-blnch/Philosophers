#include "../philo.h"

static void fork_assign(t_philo *philo, t_fork *forks, int philo_pos)
{
    int philo_nbr;

    philo_nbr = philo->table->philo_nbr;
    if (philo->id % 2 == 0) // philosophes pairs
    {
        philo->right_fork = &forks[philo_pos];
        philo->left_fork = &forks[(philo_pos + 1) % philo_nbr];
    }
    else // philosophes impairs
    {
        philo->left_fork = &forks[philo_pos];
        philo->right_fork = &forks[(philo_pos + 1) % philo_nbr];
    }
}

static void philo_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = 0;
    while (i < table->philo_nbr)
    {
        philo = &table->philos[i];
        philo->id = i + 1;
        philo->meals_count = 0;
        philo->table = table;
        //philo->last_meal_time = table->start_simulation;
        fork_assign(philo, table->forks, i);
        i++;
    }
}

void    data_init(t_table *table)
{
    int i;

    i = 0;
    table->end_simulation = false;
    table->philos = mallocation(sizeof(t_philo) * table->philo_nbr);
    mutex_handle(table->table_mutex, INIT);
    table->forks = mallocation(sizeof(t_fork) * table->philo_nbr);
    while(i < table->philo_nbr)
    {
        mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
        i++;
    }
    philo_init(table);
}
