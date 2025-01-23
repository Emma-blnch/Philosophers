#include "../philo.h"

static void philo_eat(t_philo *philo)
{
    mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo);
    mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    philo->meals_count++;
    write_status(EATING, philo);
    precise_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->limit_meals > 0 && philo->meals_count == philo->table->limit_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
    mutex_handle(&philo->first_fork->fork, UNLOCK);
    mutex_handle(&philo->second_fork->fork, UNLOCK);
}

static void thinking(t_philo *philo)
{
    write_status(THINKING, philo);
}

void    *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->table);
    if (philo->id % 2 == 0)
        usleep(300);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
    while (!simulation_finished(philo->table))
    {
        if (philo->full) // peut etre utiliser get bool pour que ce soit thread safe
            break ;
        philo_eat(philo);
        write_status(SLEEPING, philo);
        precise_usleep(philo->table->time_to_sleep, philo->table);
        thinking(philo);
    }
    
    return (NULL);
}

void handle_one_philo(t_table *table)
{
    t_philo *philo;
    
    philo = &table->philos[0];
    write_status(TAKE_FIRST_FORK, philo);
    precise_usleep(table->time_to_die, table);
    write_status(DIED, philo);
}

void    dinner_start(t_table *table)
{
    int         i;

    i = 0;
    table->start_simulation = get_time(MILLISECOND);
    if (table->philo_nbr == 1)
        return (handle_one_philo(table));
    else
    {
        while (i < table->philo_nbr)
        {
            thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
            i++;
        }
    }
    thread_handle(&table->monitor, monitor_dinner, table, CREATE);
    set_bool(&table->table_mutex, &table->all_threads_ready, true);
    i = 0;
    while (i < table->philo_nbr)
    {
        thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
        i++;
    }
    set_bool(&table->table_mutex, &table->end_simulation, true);
    thread_handle(&table->monitor, NULL, NULL, JOIN);
}
