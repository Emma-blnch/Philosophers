/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:44:12 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 14:59:38 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "philo.h"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_status;

// typedef struct s_fork
// {
// 	t_mtx		fork;
// 	int			fork_id;
// }	t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_count;
	long		last_meal_time;
	bool		full;
	// t_fork		*first_fork;
	// t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
	t_mtx		philo_mutex;
	t_mtx		fork_l;
	t_mtx		*fork_r;
}	t_philo;

struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		limit_meals;
	long		start_simulation;
	//long		threads_running_nbr;
	bool		end_simulation;
	//bool		all_threads_ready;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	//pthread_t	monitor;
	//t_fork		*forks;
	t_philo		*philos;
};

#endif
