/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 00:17:10 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/03 11:59:52 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include "codexion.h"
# include <stdlib.h>
# include <sys/time.h>

long	get_ms(void);
long	get_passed_time(t_data data);
#endif
