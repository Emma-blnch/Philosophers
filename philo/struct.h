# ifndef STRUCT_H
#define STRUCT_H

#include "philo.h"

typedef pthread_mutex_t t_mtx;
typedef struct s_table  t_table;

typedef enum e_opcode
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,
}   t_opcode;

typedef struct s_fork
{
    t_mtx   fork;
    int     fork_id; // pas sur que ce soit utile
}           t_fork;

typedef struct s_philo
{
    int         id;
    long        meals_count;
    long        last_meal_time;
    t_fork      *right_fork;
    t_fork      *left_fork;
    pthread_t   thread_id;
    t_table     *table;
}               t_philo;

struct s_table
{
    long    philo_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    limit_meals;
    long    start_simulation;
    bool    end_simulation;
    bool    all_threads_ready;
    t_mtx   table_mutex;
    t_fork  *forks;
    t_philo *philos;
};

#endif