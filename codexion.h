/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:13:39 by bclairot          #+#    #+#             */
/*   Updated: 2026/02/26 13:13:39 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
    #define CODEXION_H

    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct s_coder
    {
        bool compile; // TODO Mettre un autre timer ici pour la derniere fois quil a reset son burnout
        bool debug;
        bool refactor;
        bool burnout;
    } t_coder;
    
    typedef struct s_timer
    {
        long starting_time;
        int time_to_burnout;
        int time_to_compile;
        int time_to_debug;
        int time_to_refactor;
        int dongle_cooldown;
    } t_timer;

    typedef struct s_data
    {
        t_timer timers;
        t_coder *coders;
        int nbr_of_coders;
        bool *available_dongle;
        bool scheduler_fifo;
        int number_of_compiles_required;
    } t_data;

#endif
