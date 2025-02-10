/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:14:00 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 15:25:14 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void	error_exit(const char *error)
// {
// 	printf(R"%s\n"RESET, error);
// 	exit(EXIT_FAILURE);
// }

// void	*mallocation(size_t bytes)
// {
// 	void	*result;

// 	result = malloc(bytes);
// 	if (result == NULL)
// 		error_exit("Malloc failed");
// 	return (result);
// }

// void	wait_for_threads_and_clean(t_table *table, pthread_t supervisor)
// {
// 	int	i;

// 	i = 0;
// 	while (i < table->philo_nbr)
// 	{
// 		thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
// 		i++;
// 	}
// 	thread_handle(&supervisor, NULL, NULL, JOIN);
// 	free_resources(table);
// }

// long	get_time(t_time_code timecode)
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL))
// 		error_exit("gettimeofday failed");
// 	if (timecode == SECOND)
// 		return (tv.tv_sec + (tv.tv_usec / 1e6));
// 	else if (timecode == MILLISECOND)
// 		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
// 	else if (timecode == MICROSECOND)
// 		return ((tv.tv_sec * 1e6) + tv.tv_usec);
// 	else
// 		error_exit("Wrong input to get_time");
// 	return (1337);
// }

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}

void	print(t_philo *philo, char *str)
{
	long int	time;

	pthread_mutex_lock(&(philo->info->print));
	time = timestamp() - philo->info->t_start;
	if (!philo->info->stop && time >= 0 \
			&& time <= INT_MAX && !is_dead(philo, 0))
		printf("%lld %d %s", timestamp() - philo->info->t_start, philo->n, str);
	pthread_mutex_unlock(&(philo->info->print));
}

void	error_exit(const char *error)
{
	printf(R"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}
