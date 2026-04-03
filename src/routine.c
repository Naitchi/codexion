/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 09:51:39 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/14 14:45:58 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"

void	turn_dongles_in(t_data *data, int first, int second)
{
	pthread_mutex_lock(&data->dongle[first].mutex_dongle);
	pthread_mutex_lock(&data->dongle[second].mutex_dongle);
	data->dongle[second].available = !data->dongle[second].available;
	data->dongle[second].available_time = get_ms()
		+ data->timers.dongle_cooldown;
	data->dongle[first].available = !data->dongle[first].available;
	data->dongle[first].available_time = get_ms()
		+ data->timers.dongle_cooldown;
	pthread_mutex_unlock(&data->dongle[second].mutex_dongle);
	pthread_mutex_unlock(&data->dongle[first].mutex_dongle);
}

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
	int	other_first;
	int	other_second;
	long	elapsed_current;

	if (data->scheduler_fifo)
		return (true);
	elapsed_current = get_passed_time(get_starting_time(&data->coders[index_coder]));
	other_first = get_coder_on_dongle(data, index_coder, first);
	other_second = get_coder_on_dongle(data, index_coder, second);
	if (other_first >= 0 && other_first != index_coder
		&& get_passed_time(get_starting_time(&data->coders[other_first]))
		> elapsed_current)
		return (false);
	if (other_second >= 0 && other_second != index_coder
		&& other_second != other_first
		&& get_passed_time(get_starting_time(&data->coders[other_second]))
		> elapsed_current)
		return (false);
	return (true);
}

static bool	can_take_dongles(t_data *data, int first, int second, int index_coder)
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
	printf("%ld %d has taken a dongle\n",
		get_passed_time(data->starting_time), index_coder + 1);
	data->dongle[first].available = !data->dongle[first].available;
	printf("%ld %d has taken a dongle\n",
		get_passed_time(data->starting_time), index_coder + 1);
}

// TODO je pourrais faire un fichier dongle.c si besoin
int	take_dongles(t_data *data, int first, int second, int index_coder)
{
	int	rslt;

	rslt = 0;
	if (!pthread_mutex_lock(&data->dongle[second].mutex_dongle)
		&& !pthread_mutex_lock(&data->dongle[first].mutex_dongle))
	{
		if (can_take_dongles(data, first, second, index_coder))
		{
			pick_dongles(data, first, second, index_coder);
			rslt = 1;
		}
	}
	else
		rslt = 0;
	pthread_mutex_unlock(&data->dongle[second].mutex_dongle);
	pthread_mutex_unlock(&data->dongle[first].mutex_dongle);
	return (rslt);
}

int	is_dongles_available(t_data *data, int index_coder) // TODO rename: elle sert a savoir quelles index de dongle, le coder a besoin 
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

void let_go_dongles(t_data *data, int index_coder)
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

static void	compile_cycle(t_data *data, int index_coder)
{
	action(data, index_coder, "is compiling", data->timers.time_to_compile);
	let_go_dongles(data, index_coder);
	action(data, index_coder, "is debugging", data->timers.time_to_debug);
	action(data, index_coder, "is refactoring", data->timers.time_to_refactor);
	inc_compilation_nbr(&data->coders[index_coder]);
}

static bool	keep_routine_running(t_data *data, int index_coder)
{
	if (get_stop(data))
		return (false);
	if (get_compilation_nbr(&data->coders[index_coder])
		> data->number_of_compiles_required)
		return (false);
	return (true);
}

void	*routine(void *arg)
{
	t_thread_data	*obj;
	int				index_coder;
	t_data			*data;

	obj = (t_thread_data *)arg;
	index_coder = obj->index_coder;
	data = obj->data;
	while (keep_routine_running(data, index_coder))
	{
		if (is_dongles_available(data, index_coder))
			compile_cycle(data, index_coder);
	}
	return (NULL);
}
