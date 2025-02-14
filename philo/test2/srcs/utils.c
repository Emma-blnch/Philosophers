/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:15:53 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/14 10:27:17 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_timestamp();
	while ((get_timestamp() - start_time) < time_in_ms)
		usleep(100);
}

void	write_state(char *str, t_phil *phil)
{
	long	cur_time;

	cur_time = get_timestamp() - phil->params->start_time;
	pthread_mutex_lock(&(phil->params->console_mutex));
	if (!is_dead(phil))
		printf("%03ld %d %s\n", cur_time, phil->pos, str);
	pthread_mutex_unlock(&(phil->params->console_mutex));
}

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	error_exit(const char *error)
{
	printf(R"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *nptr)
{
	int		num;
	size_t	i;

	i = 0;
	num = 0;
	if (nptr[0] == '\0' || !nptr)
    	error_exit("Empty argument is not allowed");
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
		error_exit("Only positive values allowed");
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] != '\0')
		error_exit("Invalid characters in input");
	return (num);
}

// int	ft_atoi(const char *nptr)
// {
// 	int		sign;
// 	int		num;
// 	size_t	i;

// 	i = 0;
// 	sign = 1;
// 	num = 0;
// 	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
// 		i++;
// 	if ((nptr[i] == '-' || nptr[i] == '+'))
// 	{
// 		if ((nptr[i + 1] == '-' || nptr[i + 1] == '+'))
// 			return (0);
// 		if (nptr[i] == '-')
// 			sign *= -1;
// 		i++;
// 	}
// 	while (nptr[i] >= '0' && nptr[i] <= '9')
// 	{
// 		num = num * 10 + (nptr[i] - '0');
// 		i++;
// 	}
// 	return (num * sign);
// }
