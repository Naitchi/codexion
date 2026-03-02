/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:13:09 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/02 10:13:09 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

void toggle_dongles(t_data data, int index_coder, int index_l, int index_r)
{
    // TODO voir pour les muthex (est ce que je peux passer un muthexlock en parametre ? comme ca je les lock dans check si dispo et ensuite je les envoies ici et pas besoin de delock)
    data.available_dongle[index_l] = !data.available_dongle[index_l]
    printf("%ld %d has taken a dongle\n",get_passed_time(data), index_coder+1);
    data.available_dongle[index_r] = !data.available_dongle[index_r]
    printf("%ld %d has taken a dongle\n",get_passed_time(data), index_coder+1);
}

void action(t_data data, int index_coder, char* annonce, int time)
{
    printf("%ld %d %s\n",get_passed_time(data), index_coder+1, annonce);
    ft_sleep(time);
}

void routine(t_data data)
{
    
}
