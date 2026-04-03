/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:34:40 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/14 13:23:26 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	init_coders(t_data *data, int nbr_of_coders)
{
	int	i;

	i = 0;
	data->nbr_of_coders = nbr_of_coders;
	data->coders = malloc(sizeof(t_coder) * nbr_of_coders);
	if (!data->coders)
		return (error(1, "Problem with the malloc in init_coders, "
				"close some applications and retry."));
	while (i < nbr_of_coders)
	{
		data->coders[i].number_of_compiles_done = 0;
		pthread_mutex_init(&data->coders[i].number_of_compiles_mutex, NULL);
		data->coders[i].starting_time = get_ms();
		pthread_mutex_init(&data->coders[i].starting_time_mutex, NULL);
		i++;
	}
	return (0);
}

int	init_dongles(t_data *data, int nbr_of_coders)
{
	int	i;

	i = 0;
	data->dongle = malloc(sizeof(t_dongle) * nbr_of_coders);
	if (!data->dongle)
	{
		free(data->coders);
		return (error(1, "Problem with the malloc in init_dongles, "
				"close some applications and retry."));
	}
	while (i < nbr_of_coders)
	{
		data->dongle[i].available = true;
		data->dongle[i].available_time = 0;
		pthread_mutex_init(&data->dongle[i].mutex_dongle, NULL);
		i++;
	}
	return (0);
}

int init_threads(t_data *data, pthread_t **threads)
{
	(*threads) = malloc(sizeof(pthread_t) * (data->nbr_of_coders + 1));
	if (!(*threads))
	{
		free(data->coders);
		free(data->dongle);
		return (error(1, "Problem with the malloc in init_threads,"
			" close some applications and retry."));
	}
	memset(*threads, 0, sizeof(pthread_t) * (data->nbr_of_coders + 1));
	return (0);
}

int init_threads_data(t_data *data, pthread_t **threads, t_thread_data **threads_data)
{
	int i;

	i = 0;
	(*threads_data) = malloc(sizeof(t_thread_data) * (data->nbr_of_coders + 1));
	if (!*threads_data)
	{
		free(*threads);
		free(data->coders);
		free(data->dongle);
		return (error(1, "Problem with the malloc in init_threads_data,"
			" close some applications and retry."));
	}
	memset(*threads_data, 0, sizeof(t_thread_data) * (data->nbr_of_coders + 1));
	while (i < data->nbr_of_coders)
	{
		(*threads_data)[i] = (t_thread_data){ .index_coder = i, .data = data };
		i++;
	}
	return (0);
}
