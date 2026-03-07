/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:19:05 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/05 16:19:05 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

# include "codexion.h"

void    set_stop(t_data *data);
bool    get_stop(t_data *data);
void    inc_compilation_nbr(t_coder *coder);
int     get_compilation_nbr(t_coder *coder);
void    set_starting_time(t_coder *coder);
long     get_starting_time(t_coder *coder);
#endif
