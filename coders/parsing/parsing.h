/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:12:52 by bclairot          #+#    #+#             */
/*   Updated: 2026/04/05 11:44:37 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../codexion_types.h"
# include "../utils/utils.h"
# include "error_handling/error_handling.h"
# include <stdlib.h>
# include <string.h>

int	verfication(int argc, char *argv[]);
int	init_coders(t_data *data, int nbr_of_coders);
int	init_dongles(t_data *data, int nbr_of_coders);
int	init_threads(t_data *data, pthread_t **threads);
int	init_threads_data(t_data *data, pthread_t **threads,
		t_thread_data **threads_data);
int	parsing(t_data *data, int argc, char *argv[]);

#endif
