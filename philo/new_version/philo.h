/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:49:50 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 18:57:01 by ema_blnch        ###   ########.fr       */
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

# include "struct.h"

# define RESET   "\033[0m" /* reset to default */
# define BLACK   "\033[1;30m" 
# define R       "\033[1;31m" /* bold red */
# define G       "\033[1;32m" /* bold green */
# define Y       "\033[1;33m" /* bold yellow */
# define B       "\033[1;34m" /* bold blue */
# define M       "\033[1;35m" /* bold magenta */
# define C       "\033[1;36m" /* bold cyan */
# define W       "\033[1;37m" /* bold white */

// Main
int		main(int argc, char **argv);

// Init
int		var_init(t_info *data);
int		philo_init(t_info *data);
void	parse_input(t_info *table, char **argv);

// Diner
void	*philo_life(void *phi);
void	philo_eat(t_philo *philo);
void	take_fork(t_philo *philo);

// Check death
int		is_dead(t_philo *philo, int nb);
void	*check_death(void *phi);

// Utils
long	ft_atol(const char *string);
long	get_current_timestamp(void);
void	ft_usleep(int ms);
void	error_exit(const char *error);
void	print(t_philo *philo, char *str);

// Free
void	free_resources(t_info *data);

#endif