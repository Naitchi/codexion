/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:19:02 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/06 16:34:03 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutex.h"

bool get_stop(t_data *data) // TODO faire un fichier setter / getter ? 
{
    bool stop; 

    stop = 0;
    pthread_mutex_lock(&data->stop_mutex);
    stop = data->stop;
    pthread_mutex_unlock(&data->stop_mutex);
    return (stop);
}

void set_stop(t_data *data)
{
    printf("STOP\n");
    pthread_mutex_lock(&data->stop_mutex);
    data->stop = true;
    pthread_mutex_unlock(&data->stop_mutex);
}

int get_compilation_nbr(t_coder *coder)
{
    int nbr; 

    nbr = 0;
    pthread_mutex_lock(&coder->number_of_compiles_mutex);
    nbr = coder->number_of_compiles_done;
    pthread_mutex_unlock(&coder->number_of_compiles_mutex);
    return (nbr);
}

void inc_compilation_nbr(t_coder *coder)
{
    pthread_mutex_lock(&coder->number_of_compiles_mutex);
    coder->number_of_compiles_done++;
    pthread_mutex_unlock(&coder->number_of_compiles_mutex);
}
