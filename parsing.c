/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 12:32:19 by bclairot          #+#    #+#             */
/*   Updated: 2026/02/28 12:32:19 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "error_handling.h"

static int check_if_int_positif(char *str)
{
    int i;
    long result;

    i = 0;
    result = 0;

    if (!str || !str[0])
        return (1);

    while (str[i])
    {
        if (str[i] > '9' || str[i] < '0')
            return (1);

        result *= 10;
        result += str[i] - '0';
        if (result > 2147483647)
            return (1);

        i++;
    }
    return (0);
}

static int verfication(int argc, char* argv[])
{
    int i;

    i = 1;
    if (argc < 9 || argc > 9) // TODO voir si ca marche cette merde ↓
        return (error(1,
            "Not enough/too much args. To launch the program you have to do:"
            " ./codexion number_of_coders time_to_burnout time_to_compile "
            "time_to_debug time_to_refactor number_of_compiles_required "
            "dongle_cooldown scheduler"));
    while (i < (argc - 1))
    {
        if (i == 8 && (strcmp(argv[i], "fifo") || strcmp(argv[i], "edf"))) // TODO voir si les strcmp la sont bons ou pas 
            return error(1, "The scheduler can only be edf or fifo.");
        else if (check_if_int_positif(argv[i]))
            return error(1, "Timer/number should be numbers in int range.");
        else if (atoi(argv[1]) == 0)
            return error(1, "Number of coders should be atleast one.");
        i++;
    }
    return (0);
}

// TODO si ca rentre pas dans le fichier on y met dans un fichier inizialisation et on y passe ici dans une fonction nomme parsing qui verifie et initialise  
static int init_coders(t_data* data, int nbr_of_coders)
{
    int i;
    
    i = 0;
    data->nbr_of_coders = nbr_of_coders;
    data->coders = malloc(sizeof(t_coder) * nbr_of_coders);
    if (!data->coders)
        return (1);
    while (i < nbr_of_coders)
    {
        data->coders[i].compile = false;
        data->coders[i].debug = false;
        data->coders[i].refactor = false;
        data->coders[i].burnout = false;
        i++;
    }
    return (0);
}

static int init_data(t_data* data, int argc, char* argv[])
{
    data->nbr_of_coders = atoi(argv[1]);
    if (init_coders(data, data->nbr_of_coders))
        return (1);
    data->timers.time_to_burnout = atoi(argv[2]);
    data->timers.time_to_compile = atoi(argv[3]);
    data->timers.time_to_debug = atoi(argv[4]);
    data->timers.time_to_refactor = atoi(argv[5]);
    data->number_of_compiles_required = atoi(argv[6]);
    data->timers.dongle_cooldown = atoi(argv[7]);
    if (!strcmp(argv[8], "fifo"))
        data->scheduler_fifo = true;
    else if(!strcmp(argv[8], "edf"))
        data->scheduler_fifo = false;
    return (0);
}

int parsing(t_data *data, int argc, char* argv[])
{
    int error;
    printf("test 107\n");
    error = verfication(argc, argv);
    if (error)
        return (1);
    printf("test\n");
    error = init_data(data, argc, argv);
    if (error)
        return (1);
}
