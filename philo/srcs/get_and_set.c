#include "../philo.h"

void    set_bool(t_mtx *mutex, bool *dest, bool value)
{
    mutex_handle(mutex, LOCK);  // Verrouille le mutex
    *dest = value;             // Modifie la valeur
    mutex_handle(mutex, UNLOCK); // Déverrouille le mutex
}

bool    get_bool(t_mtx *mutex, bool *value)
{
    bool result;

    mutex_handle(mutex, LOCK);
    result = *value;
    mutex_handle(mutex, UNLOCK);
    return (result);
}

void    set_long(t_mtx *mutex, long *dest, long value)
{
    mutex_handle(mutex, LOCK);
    *dest = value;
    mutex_handle(mutex, UNLOCK);
}

long    get_long(t_mtx *mutex, long *value)
{
    long result;

    mutex_handle(mutex, LOCK);
    result = *value;
    mutex_handle(mutex, UNLOCK);
    return (result);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}