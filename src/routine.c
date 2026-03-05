/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 09:51:39 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/03 15:47:39 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"

// TODO je pourrais faire un fichier dongle.c si besoin
// TODO appeler toggle dongles a la fin de cette fonction ?
int	is_dongles_available(t_data *data, int index_coder)
{
	int	coders_nbr;
	int	l_dongle;
	int	r_dongle;

	// TODO voir pour les muthex pour pas se faire voler un dongle pendant qu'on fait le check et pour les toggles ? 
	coders_nbr = data->nbr_of_coders;
	if (coders_nbr == 1)
		return (0);
	l_dongle = index_coder - 1;
	r_dongle = index_coder;
	if (!index_coder)
		l_dongle = coders_nbr - 1;
	if (data->available_dongle[l_dongle] && data->available_dongle[r_dongle])
		return (1);
	return (0);
}

void*	routine(void* arg)
{
	t_thread_data *obj = (t_thread_data *)arg;
	int index_coder = obj->index_coder;
	t_data *data = obj->data; 
	int	l_dongle;

	l_dongle = index_coder - 1;
	if (!index_coder)
		l_dongle = data->nbr_of_coders - 1;
	while (!get_stop(data) && data->coders[index_coder].number_of_compiles_done <= data->number_of_compiles_required)
	{
		if (is_dongles_available(data, index_coder))
		{
			toggle_dongles(data, index_coder, l_dongle, index_coder);
			action(data, index_coder, "is compiling", data->timers.time_to_compile);
			toggle_dongles(data, index_coder, l_dongle, index_coder);
			action(data, index_coder, "is debugging", data->timers.time_to_debug);
			action(data, index_coder, "is refactoring", data->timers.time_to_refactor);
			data->coders[index_coder].number_of_compiles_done++;
		}
	}
	printf("coder done\n");
	return (NULL);
}
