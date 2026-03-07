/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:13:09 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/06 16:12:12 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

void	action(t_data *data, int i, char *annonce, int time)
{
	if (get_stop(data) && get_compilation_nbr(&data->coders[i]) <= data->number_of_compiles_required)
		return ;
	printf("%ld %d %s\n", get_passed_time(data->starting_time), i + 1, annonce);
	ft_sleep(time);
}
