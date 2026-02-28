/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:13:36 by bclairot          #+#    #+#             */
/*   Updated: 2026/02/26 13:13:36 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "parsing.h"

int main(int argc, char *argv[])
{
    t_data data;
    memset(&data, 0, sizeof(t_data));

    if (parsing(&data, argc, argv))
        return (1);
    printf("test i \n");
    printf("%d\n", data.nbr_of_coders);
    // data->coders
    printf("%d\n", data.timers.time_to_burnout);
    printf("%d\n", data.timers.time_to_compile);
    printf("%d\n", data.timers.time_to_debug);
    printf("%d\n", data.timers.time_to_refactor);
    printf("%d\n", data.number_of_compiles_required);
    printf("%d\n", data.timers.dongle_cooldown);
    return (0);
}
