/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:48:44 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/06 14:57:20 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	monitoring(t_data *data)
{
	int	i;
	int	coders_done;

	coders_done = 0;
	while (!get_stop(data) && coders_done < data->nbr_of_coders)
	{
		coders_done = 0;
		i = 0;
		while (i < data->nbr_of_coders)
		{
			if (get_passed_time(get_starting_time(&data->coders[i])) >= data->timers.time_to_burnout)
			{
				printf("%ld %d burned out\n", get_passed_time(data->starting_time), i + 1);
				set_stop(data);
			}
			if (get_compilation_nbr(&data->coders[i]) >= data->number_of_compiles_required)
				coders_done++;
			i++;
		}
	}
	printf("%ld DONE\n", get_passed_time(data->starting_time));
	set_stop(data);
}

void cut_everything(pthread_t *threads, t_data* data)
{
	int i;

	i = 0;
	while (i < data->nbr_of_coders)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return ;
}
