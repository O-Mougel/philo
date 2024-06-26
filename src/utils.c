/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:11:32 by omougel           #+#    #+#             */
/*   Updated: 2024/06/26 11:48:02 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void  error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void  precise_usleep(long usec, t_table *table)
{
	long  start;
	long  elapsed;
	long  rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finnished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (gettime(MICROSECOND) - start < usec)
				;
	}
}

long  gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec *1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime!");
	return (1337);
}

void  clean(t_table	*table)
{
	t_philo	*philo;
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handler(&philo->philo_mutex, DESTROY);

	}
	safe_mutex_handler(&table->write_mutex, DESTROY);
	safe_mutex_handler(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
