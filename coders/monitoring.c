/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:48:44 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/13 11:20:24 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void*	monitoring(void *arg)
{
	int	i;
	int	coders_done;
	t_data *data = (t_data *)arg;

	coders_done = 0;
	while (!get_stop(data) && coders_done < data->nbr_of_coders)
	{
		coders_done = 0;
		i = 0;
		while (i < data->nbr_of_coders)
		{
			if (get_passed_time(get_starting_time(&data->coders[i])) >= data->timers.time_to_burnout)
			{
				pthread_mutex_lock(&data->print_mutex);
				printf("%ld %d burned out\n", get_passed_time(data->starting_time), i + 1);
				pthread_mutex_unlock(&data->print_mutex);
				set_stop(data);
			}
			if (get_compilation_nbr(&data->coders[i]) >= data->number_of_compiles_required)
				coders_done++;
			i++;
		}
	}
	set_stop(data);
	return (NULL);
}

int cut_everything(pthread_t *threads, t_data* data, pthread_t *monitoring_thread, int code)
{
	int i;

	i = 0;
	while (threads[i])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	if (monitoring_thread)
		pthread_join(*monitoring_thread, NULL);
	return (code);
}
