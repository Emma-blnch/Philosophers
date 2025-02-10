/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:27:59 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 18:50:50 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atol(const char *string)
{
	long	result;
	size_t	index;

	index = 0;
	result = 0;
	if (string[0] == '\0' || !string)
    	error_exit("Empty argument is not allowed");
	while (string[index] == ' ' || (string[index] >= 9 && string[index] <= 13))
		index++;
	if (string[index] == '+')
		index++;
	else if (string[index] == '-')
		error_exit("Only positive values allowed");
	while (string[index] >= '0' && string[index] <= '9')
	{
		if (result > (LONG_MAX - (string[index] - '0')) / 10)
			error_exit("Number too large");
		result = result * 10 + (string[index] - '0');
		index++;
	}
	while (string[index] == ' ' || (string[index] >= 9 && string[index] <= 13))
		index++;
	if (string[index] != '\0')
		error_exit("Invalid characters in input");
	return (result);
}
