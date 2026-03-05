/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:13:39 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/04 14:46:27 by bclairot         ###   ########.fr       */
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
	int		number_of_compiles_done;
	long	starting_time;
	bool	compile;
	bool	debug;
	bool	refactor;
	bool	burnout;
}			t_coder;

typedef struct s_timer
{
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		dongle_cooldown;
}			t_timer;

typedef struct s_data
{
	long	starting_time;
	t_timer	timers;
	t_coder	*coders;
	int		nbr_of_coders;
	bool	*available_dongle;
	bool	scheduler_fifo;
	int		number_of_compiles_required;
	bool	stop;
	pthread_mutex_t stop_mutex;
}			t_data;

typedef struct s_thread_data
{
	int 	index_coder;
	t_data 	*data;
} 			t_thread_data;

# include "parsing/initialization.h"
# include "routine.h"
# include "monitoring.h"

#endif
