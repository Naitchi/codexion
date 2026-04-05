/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:13:09 by bclairot          #+#    #+#             */
/*   Updated: 2026/04/05 11:44:37 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

void	action(t_data *data, int i, char *annonce, int time)
{
	if (get_stop(data))
		return ;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d %s\n", get_p_t(data->starting_time), i + 1, annonce);
	pthread_mutex_unlock(&data->print_mutex);
	ft_sleep(time);
}
