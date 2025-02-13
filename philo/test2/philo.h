/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:13:34 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/13 14:14:27 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <unistd.h> // usleep
# include <stdlib.h> // malloc, free
# include <sys/time.h> // gettimeofday
# include <pthread.h> // threads, mutex
# include <stdbool.h> // bool
# include <limits.h> // long max et long min
# include <string.h> // memset
# include <errno.h> 

# define RESET   "\033[0m" /* reset to default */
# define BLACK   "\033[1;30m" 
# define R       "\033[1;31m" /* bold red */
# define G       "\033[1;32m" /* bold green */
# define Y       "\033[1;33m" /* bold yellow */
# define B       "\033[1;34m" /* bold blue */
# define M       "\033[1;35m" /* bold magenta */
# define C       "\033[1;36m" /* bold cyan */
# define W       "\033[1;37m" /* bold white */

typedef struct s_params
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_max;
	long			start_time;
	pthread_mutex_t	console_mutex;
	int				is_dead;
	pthread_mutex_t	m_is_dead;
	pthread_t		death_thread;
}	t_params;

typedef struct s_fork
{
	int				used;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_phil
{
	pthread_t		thread;
	int				pos;
	long			last_meal;
	pthread_mutex_t	m_last_meal;
	int				meal_count;
	t_fork			*r_fork;
	int				r_taken;
	t_fork			*l_fork;
	int				l_taken;
	t_params		*params;
}	t_phil;

// death.c
int		is_dead(t_phil *phil);
void	*check_philos_death(void *arg);
int		stop_threads(t_phil *phil);

// forks.c
void	take_fork(char fork_name, t_phil *phil);
void	release_fork(char fork_name, t_phil *phil);
void	release_forks_and_sleep(t_phil *phil);

// init.c
int		create_philos(t_phil **philos, t_fork **forks, t_params	*params);
int		init_params(t_params *params, int argc, char **argv);

// main.c
void	*philo_life(void *arg);

// threads.c
int		create_threads(t_phil **philos, t_params *params);
int		wait_threads(t_phil **philos, t_params *params);

// utils.c
int		ft_atoi(const char *nptr);
void	ft_usleep(long int time_in_ms);
void	write_state(char *str, t_phil *phil);
long	get_timestamp(void);

#endif
