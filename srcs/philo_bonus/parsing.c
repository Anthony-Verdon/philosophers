/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:03:21 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 14:19:37 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

int	parsing(int argc, char **argv)
{
	int	i;
	int	j;
	int	arg;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (argv[i])
	{
		arg = ft_atoll(argv[i]);
		if (arg > INT_MAX || arg <= 0)
			return (1);
		j = 0;
		if (argv[i][j] == '+' || argv[i][j] == '-')
				j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
