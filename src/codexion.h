/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:13:39 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/06 16:10:08 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_coder
{
	int				number_of_compiles_done;
	pthread_mutex_t	number_of_compiles_mutex;
	long			starting_time;
	bool			compile;
	bool			debug;
	bool			refactor;
	bool			burnout;
	// TODO supprimer toutes les bool ou alors mettre les timings a la place comme ca moins de mutex a faire
}					t_coder;

typedef struct s_timer
{
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				dongle_cooldown;
}					t_timer;

typedef struct s_dongle
{
	bool			available;
	pthread_mutex_t	mutex_dongle;
}					t_dongle;

typedef struct s_data
{
	long			starting_time;
	t_timer			timers;
	t_coder			*coders;
	int				nbr_of_coders;
	t_dongle		*dongle;
	bool			scheduler_fifo;
	int 			number_of_compiles_required;
	bool			stop;
	pthread_mutex_t	stop_mutex;
	// TODO faire une structure seulement pour les mutex (surement une mirroir mais avec certaine en moins)
}					t_data;

typedef struct s_thread_data
{
	int				index_coder;
	t_data			*data;
}					t_thread_data;

# include "monitoring.h"
# include "parsing/initialization.h"
# include "routine.h"

#endif
