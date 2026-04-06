/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_dongles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:58:39 by bclairot          #+#    #+#             */
/*   Updated: 2026/04/06 15:39:54 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	get_coder_on_dongle(t_data *data, int index_coder, int index_dongle)
{
	int	other_coder;

	other_coder = (index_dongle + 1) % data->nbr_of_coders;
	if (index_coder == index_dongle)
		return (other_coder);
	if (index_coder == other_coder)
		return (index_dongle);
	return (-1);
}

bool	edf(t_data *data, int first, int second, int index_coder)
{
	int		other_first;
	int		other_second;
	long	elapsed_current;

	if (data->scheduler_fifo)
		return (true);
	elapsed_current = get_p_t(get_s_t(&data->coders[index_coder]));
	other_first = get_coder_on_dongle(data, index_coder, first);
	other_second = get_coder_on_dongle(data, index_coder, second);
	if (other_first >= 0 && other_first != index_coder
		&& (get_p_t(get_s_t(&data->coders[other_first])) > elapsed_current
			|| !edf_compilation_tie_break(data, index_coder,
				other_first, other_second)))
		return (false);
	if (other_second >= 0 && other_second != index_coder
		&& other_second != other_first
		&& (get_p_t(get_s_t(&data->coders[other_second])) > elapsed_current
			|| !edf_compilation_tie_break(data, index_coder,
				other_first, other_second)))
		return (false);
	return (true);
}

static bool	can_take_dongles(t_data *data, int first, int second,
		int index_coder)
{
	if (!data->dongle[second].available)
		return (false);
	if (!data->dongle[first].available)
		return (false);
	if (data->dongle[second].available_time >= get_ms())
		return (false);
	if (data->dongle[first].available_time >= get_ms())
		return (false);
	if (!edf(data, first, second, index_coder))
		return (false);
	return (true);
}

static void	pick_dongles(t_data *data, int first, int second, int index_coder)
{
	set_starting_time(&data->coders[index_coder]);
	data->dongle[second].available = !data->dongle[second].available;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d has taken a dongle\n", get_p_t(data->starting_time),
		index_coder + 1);
	data->dongle[first].available = !data->dongle[first].available;
	printf("%ld %d has taken a dongle\n", get_p_t(data->starting_time),
		index_coder + 1);
	pthread_mutex_unlock(&data->print_mutex);
}

int	take_dongles(t_data *data, int first, int second, int index_coder)
{
	if (pthread_mutex_lock(&data->dongle[first].mutex_dongle) != 0)
		return (0);
	if (pthread_mutex_lock(&data->dongle[second].mutex_dongle) != 0)
	{
		pthread_mutex_unlock(&data->dongle[first].mutex_dongle);
		return (0);
	}
	if (can_take_dongles(data, first, second, index_coder))
	{
		pick_dongles(data, first, second, index_coder);
		pthread_mutex_unlock(&data->dongle[second].mutex_dongle);
		pthread_mutex_unlock(&data->dongle[first].mutex_dongle);
		return (1);
	}
	pthread_mutex_unlock(&data->dongle[second].mutex_dongle);
	pthread_mutex_unlock(&data->dongle[first].mutex_dongle);
	return (0);
}
