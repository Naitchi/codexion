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

#include "codexion.h"

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
