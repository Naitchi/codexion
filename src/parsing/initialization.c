/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 23:40:25 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/04 14:32:49 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

static int	init_coders(t_data *data, int nbr_of_coders)
{
	int	i;

	i = 0;
	data->nbr_of_coders = nbr_of_coders;
	data->coders = malloc(sizeof(t_coder) * nbr_of_coders);
	if (!data->coders)
		return (error(1, "Problem with the malloc in init_coders,
				close some applications and retry."));
	while (i < nbr_of_coders)
	{
		data->coders[i].compile = false;
		data->coders[i].debug = false;
		data->coders[i].refactor = false;
		data->coders[i].burnout = false;
		i++;
	}
	return (0);
}

static int	init_dongles(t_data *data, int nbr_of_coders)
{
	int	i;

	i = 0;
	data->available_dongle = malloc(sizeof(bool) * nbr_of_coders);
	if (!data->available_dongle)
	{
		free(data->coders);
		return (error(1, "Problem with the malloc in init_dongles,
				close some applications and retry."));
	}
	while (i < nbr_of_coders)
	{
		data->available_dongle[i] = true;
		i++;
	}
	return (0);
}

static int	init_data(t_data *data, int argc, char *argv[])
{
	data->stop = false;
	data->nbr_of_coders = atoi(argv[1]);
	if (init_coders(data, data->nbr_of_coders))
		return (1);
	data->timers.time_to_burnout = atoi(argv[2]);
	data->timers.time_to_compile = atoi(argv[3]);
	data->timers.time_to_debug = atoi(argv[4]);
	data->timers.time_to_refactor = atoi(argv[5]);
	data->number_of_compiles_required = atoi(argv[6]);
	data->timers.dongle_cooldown = atoi(argv[7]);
	if (!strcmp(argv[8], "fifo"))
		data->scheduler_fifo = true;
	else if (!strcmp(argv[8], "edf"))
		data->scheduler_fifo = false;
	if (init_dongles(data, data->nbr_of_coders))
		return (1);
	return (0);
}

int	parsing(t_data *data, int argc, char *argv[])
{
	int	error;

	error = verfication(argc, argv);
	if (error)
		return (1);
	error = init_data(data, argc, argv);
	if (error)
		return (1);
}
