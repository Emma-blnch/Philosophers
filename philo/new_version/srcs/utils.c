/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:14:00 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 18:54:54 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = get_current_timestamp();
	while (get_current_timestamp() - time < ms)
		usleep(ms / 10);
}

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
// // More precise usleep than the original
// void	precise_usleep(long usec)
// {
// 	long	start;
// 	long	elapsed;

// 	start = get_time(MICROSECOND);
// 	while (1)
// 	{
// 		elapsed = get_time(MICROSECOND) - start;
// 		if (elapsed >= usec)
// 			break ;
// 		if (usec - elapsed > 1000)
// 			usleep((usec - elapsed) / 2);
// 	}
// }

void	print(t_philo *philo, char *str)
{
	long int	time;

	pthread_mutex_lock(&(philo->info->print));
	time = get_current_timestamp() - philo->info->t_start;
	if (!philo->info->stop && time >= 0 \
			&& time <= INT_MAX && !is_dead(philo, 0))
		printf("%ld %d %s", get_current_timestamp() - philo->info->t_start, philo->n, str);
	pthread_mutex_unlock(&(philo->info->print));
}

void	error_exit(const char *error)
{
	printf(R"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}
