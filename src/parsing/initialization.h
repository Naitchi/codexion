/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclairot <bclairot@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 23:41:14 by bclairot          #+#    #+#             */
/*   Updated: 2026/03/03 12:00:17 by bclairot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZATION_H
# define INITIALIZATION_H

# include "../codexion.h"
# include "error_handling/error_handling.h"
# include "verification.h"
# include "allocation.h"

int	parsing(t_data *data, int argc, char *argv[]);
#endif
