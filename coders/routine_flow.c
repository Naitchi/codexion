/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:58:26 by bclairot          #+#    #+#             */
/*   Updated: 2026/04/06 15:25:19 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	edf_compilation_tie_break(t_data *data, int index_coder,
		int other_first, int other_second)
{
	int		current_compiles;
	long	elapsed_current;

	elapsed_current = get_p_t(get_s_t(&data->coders[index_coder]));
	current_compiles = get_compi_nbr(&data->coders[index_coder]);
	if (other_first >= 0 && other_first != index_coder
		&& get_p_t(get_s_t(&data->coders[other_first])) == elapsed_current
		&& get_compi_nbr(&data->coders[other_first]) < current_compiles)
		return (false);
	if (other_second >= 0 && other_second != index_coder
		&& other_second != other_first
		&& get_p_t(get_s_t(&data->coders[other_second])) == elapsed_current
		&& get_compi_nbr(&data->coders[other_second]) < current_compiles)
		return (false);
	return (true);
}

void	turn_dongles_in(t_data *data, int first, int second)
{
	int	low;
	int	high;

	low = first;
	high = second;
	if (low > high)
	{
		low = second;
		high = first;
	}
	pthread_mutex_lock(&data->dongle[low].mutex_dongle);
	pthread_mutex_lock(&data->dongle[high].mutex_dongle);
	data->dongle[second].available = !data->dongle[second].available;
	data->dongle[second].available_time = get_ms()
		+ data->timers.dongle_cooldown;
	data->dongle[first].available = !data->dongle[first].available;
	data->dongle[first].available_time = get_ms()
		+ data->timers.dongle_cooldown;
	pthread_mutex_unlock(&data->dongle[high].mutex_dongle);
	pthread_mutex_unlock(&data->dongle[low].mutex_dongle);
}

int	is_dongles_available(t_data *data, int index_coder)
{
	int	coders_nbr;
	int	l_dongle;
	int	r_dongle;
	int	rslt;

	rslt = 0;
	coders_nbr = data->nbr_of_coders;
	if (coders_nbr == 1)
		return (0);
	l_dongle = index_coder - 1;
	r_dongle = index_coder;
	if (!index_coder)
		l_dongle = coders_nbr - 1;
	if (l_dongle > r_dongle)
		rslt = take_dongles(data, r_dongle, l_dongle, index_coder);
	else
		rslt = take_dongles(data, l_dongle, r_dongle, index_coder);
	return (rslt);
}

void	let_go_dongles(t_data *data, int index_coder)
{
	int	coders_nbr;
	int	l_dongle;
	int	r_dongle;

	coders_nbr = data->nbr_of_coders;
	l_dongle = index_coder - 1;
	r_dongle = index_coder;
	if (!index_coder)
		l_dongle = coders_nbr - 1;
	if (l_dongle > r_dongle)
		turn_dongles_in(data, r_dongle, l_dongle);
	else
		turn_dongles_in(data, l_dongle, r_dongle);
}
