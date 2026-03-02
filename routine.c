/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 09:51:39 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/02 09:51:39 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"

void all_routines(t_data data)
{

}

// TODO y'a un monde ou celle la est static et on utilise celle du dessus dans le main
void routine(t_data data, int index_coder)
{
    int l_dongle;
    // TODO on recupe le time la et on compare a burnout en boucle (mais est ce qu'il peut mourir pendant sa routine ? oui, non ?)
    l_dongle = index_coder - 1;
    if (!index_coder)
        l_dongle = data.nbr_of_coders - 1;

    if (is_dongles_available(data, index_coder))
    {
        action(data, index_coder, "is compiling", data.timers.time_to_compile);
        toggle_dongles(data, index_coder, l_dongle, index_coder);
        action(data, index_coder, "is debugging", data.timers.time_to_debug);
        action(data, index_coder, "is refactoring", data.timers.time_to_refactor);
    }
}

// TODO je pourrais faire un fichier dongle.c si besoin 
// TODO appeler toggle dongles a la fin de cette fonction ?
int is_dongles_available(t_data data, int index_coder)
{
    int coders_nbr;
    int l_dongle;
    int r_dongle;
    // TODO voir pour les muthex pour pas se faire voler un dongle pendant qu'on fait le check
    coders_nbr = data.nbr_of_coders;
    if (coders_nbr == 1);
        return (0);
    l_dongle = index_coder - 1;
    r_dongle = index_coder;
    if (!index_coder)
        l_dongle == coders_nbr - 1;

    if (data.available_dongle[l_dongle] && data.available_dongle[r_dongle])
        return (1);
    return (0);
}
