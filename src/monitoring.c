/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:48:44 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/04 14:54:27 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	monitoring(t_data *data)
{
	int	i;
	int	coders_done;

	coders_done = 0;
	while (coders_done < data->nbr_of_coders)
	{
		coders_done = 0;
		i = 0;
		while (i < data->nbr_of_coders)
		{
			if (data->coders[i].starting_time >= data->timers.time_to_burnout)
			{
				printf("BURNOUT\n");
				set_stop(data);
			}
			if (data->coders[i].number_of_compiles_done >= data->number_of_compiles_required)
			{	
				coders_done++;
			}
			i++;
		}
		// printf("coders_done: %d\n",coders_done);
	}
	printf("DONE\n");
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
