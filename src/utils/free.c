/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:04:38 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/13 11:31:46 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

// TODO move the file to parsing/
void	free_all(pthread_t* threads, t_data* data, t_thread_data* threads_data)
{
    int	i;

    i = 0;
    while (i < data->nbr_of_coders)
    {
        pthread_mutex_destroy(&data->coders[i].number_of_compiles_mutex);
        pthread_mutex_destroy(&data->coders[i].starting_time_mutex);
		pthread_mutex_destroy(&data->dongle[i].mutex_dongle);
        i++;
    }
    pthread_mutex_destroy(&data->stop_mutex);
    pthread_mutex_destroy(&data->print_mutex);
	
	free(threads);
	free(threads_data);
	free(data->coders);
	free(data->dongle);
}
