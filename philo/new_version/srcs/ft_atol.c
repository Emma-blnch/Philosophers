/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:27:59 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/10 15:24:41 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// long	ft_atol(const char *string)
// {
// 	long	result;
// 	size_t	index;

// 	index = 0;
// 	result = 0;
// 	while (string[index] == ' ' || (string[index] >= 9 && string[index] <= 13))
// 		index++;
// 	if (string[index] == '+')
// 		index++;
// 	else if (string[index] == '-')
// 		error_exit("Only positive values allowed");
// 	while (string[index] >= '0' && string[index] <= '9')
// 	{
// 		if (result > (LONG_MAX - (string[index] - '0')) / 10)
// 			error_exit("Number too large");
// 		result = result * 10 + (string[index] - '0');
// 		index++;
// 	}
// 	while (string[index] == ' ' || (string[index] >= 9 && string[index] <= 13))
// 		index++;
// 	if (string[index] != '\0')
// 		error_exit("Invalid characters in input");
// 	return (result);
// }

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	signe;

	i = 0;
	signe = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		signe *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * signe);
}
