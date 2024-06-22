/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:02:22 by omougel           #+#    #+#             */
/*   Updated: 2024/06/21 10:04:37 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void  wait_all_threads(t_table *table)
{
	while (!set_or_get_bool(GET, &table->table_mutex, &table->all_threads_ready, -1))
		;
}
