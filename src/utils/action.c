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

void	toggle_dongles(t_data *data, int index_coder, int index_l, int index_r)
{
	// TODO voir pour les muthex (est ce que je peux passer un muthexlock en parametre ? comme ca je les lock dans check si dispo et ensuite je les envoies ici et pas besoin de delock)
	data->dongle[index_l].available = !data->dongle[index_l].available;
	printf("%ld %d has taken a dongle\n", get_passed_time(data), index_coder
		+ 1);
	data->dongle[index_r].available = !data->dongle[index_r].available;
	printf("%ld %d has taken a dongle\n", get_passed_time(data), index_coder
		+ 1);
}

void	action(t_data *data, int i, char *annonce, int time)
{
	if (get_stop(data) && get_compilation_nbr(&data->coders[i]) <= data->number_of_compiles_required)
		return ;
	printf("%ld %d %s\n", get_passed_time(data), i + 1, annonce);
	ft_sleep(time);
}
