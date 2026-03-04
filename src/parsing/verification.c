/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 12:32:19 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/03 17:17:13 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verification.h"

static int	check_if_int_positif(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (!str || !str[0])
		return (1);
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (1);
		result *= 10;
		result += str[i] - '0';
		if (result > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

int	verfication(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 9 || argc > 9)
		return (error(1,
				"Not enough/too much args.\nTo launch the program you "
				"have to do:\n\t./codexion number_of_coders "
				"time_to_burnout time_to_compile time_to_debug "
				"time_to_refactor number_of_compiles_required "
				"dongle_cooldown scheduler\n"));
	while (i < argc)
	{
		if (i == 8 && strcmp(argv[i], "fifo") && strcmp(argv[i], "edf"))
			return (error(1, "The scheduler can only be edf or fifo.\n"));
		else if (i != 8 && check_if_int_positif(argv[i]))
			return (error(1, "Timer/number should be numbers in int range.\n"));
		else if (atoi(argv[1]) == 0)
			return (error(1, "Number of coders should be atleast one.\n"));
		i++;
	}
	return (0);
}
