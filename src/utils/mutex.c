/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:19:02 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/05 16:19:02 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutex.h"

bool get_stop(t_data *data)
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
