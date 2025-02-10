/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:49:50 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 15:26:48 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

//# include "struct.h"

# define RESET   "\033[0m" /* reset to default */
# define BLACK   "\033[1;30m" 
# define R       "\033[1;31m" /* bold red */
# define G       "\033[1;32m" /* bold green */
# define Y       "\033[1;33m" /* bold yellow */
# define B       "\033[1;34m" /* bold blue */
# define M       "\033[1;35m" /* bold magenta */
# define C       "\033[1;36m" /* bold cyan */
# define W       "\033[1;37m" /* bold white */

// // Main function
// int		main(int argc, char **argv);

// // Program init
// void	parse_input(t_table *table, char **argv);
// void	data_init(t_table *table);
// void	free_resources(t_table *table);

// // Dinner sim
// void	handle_one_philo(t_table *table);
// void	dinner_start(t_table *table);
// void	*dinner_simulation(void *data);

// // Supervisor
// void	*supervisor_routine(void *arg);

// // Safe handles
// void	thread_handle(pthread_t *thread, void *(*foo)(void *),
// 			void *data, t_opcode opcode);
// void	mutex_handle(t_mtx *mutex, t_opcode opcode);

// // Setters and getters
// void	set_bool(t_mtx *mutex, bool *dest, bool value);
// bool	get_bool(t_mtx *mutex, bool *value);
// void	set_long(t_mtx *mutex, long *dest, long value);
// long	get_long(t_mtx *mutex, long *value);
// bool	simulation_finished(t_table *table);

// // Utils
// long	ft_atol(const char *string);
// void	error_exit(const char *error);
// void	*mallocation(size_t bytes);
// void	wait_all_threads(t_table *table);
// long	get_current_timestamp(void);
// long	get_time(t_time_code timecode);
// void	wait_for_threads_and_clean(t_table *table, pthread_t supervisor);
// void	precise_usleep(long usec, t_table *table);
// void	write_status(t_status status, t_philo *philo);
// void	increase_long(t_mtx *mutex, long *value);
// bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
// void	*monitor_dinner(void *data);

typedef struct l_philo
{
	int				n;
	int				m_count;
	bool			is_eating;
	pthread_t		thread;
	long int		last_eat;
	struct l_info	*info;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
}		t_philo;

typedef struct l_info
{
	int				philo_eat;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				stop;
	long int		t_start;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	dead;
}		t_info;

void		ft_usleep(int ms);
int			philo_init(t_info *data);
void		*philo_life(void *philo);
long long	timestamp(void);
int			var_init(t_info *data, char **av);
void		*philo_life(void *phi);
void		print(t_philo *philo, char *str);
int			is_dead(t_philo *philo, int nb);
int			ft_isdigit(int character);
int			ft_atoi(const char *str);
void	error_exit(const char *error);
void	free_resources(t_info *data);
void	*check_death(void *phi);

#endif
