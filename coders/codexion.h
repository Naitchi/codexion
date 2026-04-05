/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:13:39 by bclairot          #+#    #+#             */
/*   Updated: 2026/04/05 11:16:47 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "codexion_types.h"
# include "parsing/parsing.h"
# include "utils/utils.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int		codexion(t_data *data);
void	*monitoring(void *arg);
int		cut_everything(pthread_t *threads, t_data *data,
			pthread_t *monitoring_thread, int code);
bool	edf(t_data *data, int first, int second, int index_coder);
int		take_dongles(t_data *data, int first, int second, int index_coder);
int		is_dongles_available(t_data *data, int index_coder);
void	turn_dongles_in(t_data *data, int first, int second);
void	let_go_dongles(t_data *data, int index_coder);
void	*routine(void *arg);

#endif
