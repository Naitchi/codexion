/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 09:51:39 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/13 15:28:33 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"

// TODO je pourrais faire un fichier dongle.c si besoin
int take_dongles(t_data *data, int first, int second, int index_coder)
{
	int rslt;

	rslt = 0;
	pthread_mutex_lock(&data->dongle[first].mutex_dongle);
	pthread_mutex_lock(&data->dongle[second].mutex_dongle);
	if (data->dongle[second].available && data->dongle[first].available)
	{
		data->dongle[second].available = !data->dongle[second].available;
		printf("%ld %d has taken a dongle\n", get_passed_time(data->starting_time),
		index_coder + 1);
		data->dongle[first].available = !data->dongle[first].available;
		printf("%ld %d has taken a dongle\n", get_passed_time(data->starting_time),
		index_coder + 1);
		rslt = 1;
	}
	else
		rslt = 0;
	pthread_mutex_unlock(&data->dongle[second].mutex_dongle);
	pthread_mutex_unlock(&data->dongle[first].mutex_dongle);
	return (rslt);
}

void turn_dongles_in(t_data *data, int first, int second)
{
	pthread_mutex_lock(&data->dongle[first].mutex_dongle);
	pthread_mutex_lock(&data->dongle[second].mutex_dongle);
	data->dongle[second].available = !data->dongle[second].available;
	data->dongle[first].available = !data->dongle[first].available;
	pthread_mutex_unlock(&data->dongle[second].mutex_dongle);
	pthread_mutex_unlock(&data->dongle[first].mutex_dongle);
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

// TODO appeler l'action ici et le toggle dongles a la fin de cette fonction ? pour supprimer let_go_dongles()
int	is_dongles_available(t_data *data, int index_coder)
{
	int	coders_nbr;
	int	l_dongle;
	int	r_dongle;
	int rslt;

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

void*	routine(void* arg)
{
	t_thread_data *obj = (t_thread_data *)arg;
	int index_coder = obj->index_coder;
	t_data *data = obj->data; 
	int	l_dongle;

	// TODO mettre a jour coder.starting_time pour que le burnout marche !
	l_dongle = index_coder - 1;
	if (!index_coder)
		l_dongle = data->nbr_of_coders - 1;
	while (!get_stop(data) && 
			get_compilation_nbr(&data->coders[index_coder]) <= data->number_of_compiles_required) 
	{
		if (is_dongles_available(data, index_coder))
		{
			action(data, index_coder, "is compiling", data->timers.time_to_compile);
			let_go_dongles(data, index_coder);
			action(data, index_coder, "is debugging", data->timers.time_to_debug);
			action(data, index_coder, "is refactoring", data->timers.time_to_refactor);
			inc_compilation_nbr(&data->coders[index_coder]);
		}
	}
	printf("coder done\n");
	return (NULL);
}
