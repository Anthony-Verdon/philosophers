/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:14:02 by averdon           #+#    #+#             */
/*   Updated: 2023/01/12 16:21:53 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/philosophers.h"

int	overflow(int number)
{
	if (number >= 0)
		return (-1);
	else
		return (0);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	long long	to_return;
	int			is_neg;

	i = 0;
	to_return = 0;
	is_neg = 1;
	while ((nptr[i] >= '\a' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		i++;
		is_neg = -1;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		to_return = to_return * 10 + (nptr[i] - 48);
		if (to_return * is_neg > LONG_MAX || to_return * is_neg < LONG_MIN)
			return (overflow(to_return * is_neg));
		i++;
	}
	return (to_return * is_neg);
}
