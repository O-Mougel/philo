/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:01:35 by omougel           #+#    #+#             */
/*   Updated: 2024/06/26 11:28:09 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo,
				long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finnished(philo->table))
		printf(W"%-6ld"RST" %d has taken the first fork 🍽️\t\t\tn."B
			"[🍴 %d 🍴]\n"RST, elapsed, philo->id, philo->first_fork->fork_id);
	if (status == TAKE_SECOND_FORK && !simulation_finnished(philo->table))
		printf(W"%-6ld"RST" %d has taken the second fork 🍽️\t\t\tn."B
			"[🍴 %d 🍴]\n"RST, elapsed, philo->id, philo->second_fork->fork_id);
	if (status == EATING && !simulation_finnished(philo->table))
		printf(W"%-6ld"C" %d is eating 🍝\t\t\t"Y"[🍝 %ld 🍝]\n"RST, elapsed,
			philo->id, philo->meals_counter);
	if (status == SLEEPING && !simulation_finnished(philo->table))
		printf(W"%-6ld"RST" %d is sleeping 😴 \n", elapsed, philo->id);
	if (status == THINKING && !simulation_finnished(philo->table))
		printf(W"%-6ld"RST" %d is thinking 🤔\n", elapsed, philo->id);
	if (status == DIED)
		printf(RED"\t\t💀💀💀 %-6ld %d died   💀💀💀\n"RST, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (set_or_get_bool(GET, &philo->philo_mutex, &philo->full, -1))
		return ;
	safe_mutex_handler(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finnished(philo->table))
			printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		if (status == EATING && !simulation_finnished(philo->table))
			printf(W"%-6ld"C" %d is eating\n"RST, elapsed, philo->id);
		if (status == SLEEPING && !simulation_finnished(philo->table))
			printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		if (status == THINKING && !simulation_finnished(philo->table))
			printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		if (status == DIED)
			printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
	}
	safe_mutex_handler(&philo->table->write_mutex, UNLOCK);
}
