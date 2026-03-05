/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:34:40 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/05 18:34:40 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation.h"

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
		data->coders[i].compile = false;
		data->coders[i].debug = false;
		data->coders[i].refactor = false;
		data->coders[i].burnout = false;
		i++;
	}
	return (0);
}

int	init_dongles(t_data *data, int nbr_of_coders)
{
	int	i;

	i = 0;
	data->available_dongle = malloc(sizeof(bool) * nbr_of_coders);
	if (!data->available_dongle)
	{
		free(data->coders);
		return (error(1, "Problem with the malloc in init_dongles, "
				"close some applications and retry."));
	}
	while (i < nbr_of_coders)
	{
		data->available_dongle[i] = true;
		i++;
	}
	return (0);
}

int init_threads(t_data *data, pthread_t **threads)
{
	(*threads) = malloc(sizeof(pthread_t) * data->nbr_of_coders);
	if (!(*threads))
	{
		free(data->coders);
		free(data->available_dongle);
		return (error(1, "Problem with the malloc in init_threads,"
			" close some applications and retry."));
	}
	return (0);
}

int init_threads_data(t_data *data, pthread_t **threads, t_thread_data **threads_data)
{
	int i;

	i = 0;
	(*threads_data) = malloc(sizeof(t_thread_data) * data->nbr_of_coders);
	if (!*threads_data)
	{
		free(*threads);
		free(data->coders);
		free(data->available_dongle);
		return (error(1, "Problem with the malloc in init_threads_data,"
			" close some applications and retry."));
	}
	while (i < data->nbr_of_coders)
	{
		(*threads_data)[i] = (t_thread_data){ .index_coder = i, .data = data };
		i++;
	}
	return (0);
}
