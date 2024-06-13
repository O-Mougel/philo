/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:51:24 by omougel           #+#    #+#             */
/*   Updated: 2024/06/13 10:57:00 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void  dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limits_meals == 0)
		return ;
	if (table->philo_nbr == 1)
		;
	else
	{
		while (++i < table->philo_nbr)
		{
			safe_thread_handler(&table->philos[i].thread_id, dinner_simulation,
					   &table->philos[i], CREATE);
		}
	}

}
