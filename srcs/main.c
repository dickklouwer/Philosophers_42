/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/23 13:27:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/13 14:16:47 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	destroy_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(data->philo[i].lfork);
		pthread_mutex_destroy(data->philo[i].rfork);
		free((void *)data->chopsticks);
		i++;
	}
	free((void *)data->philo_t);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_data  data;

	if (parse_input(&data, argv, argc))
		return (EXIT_FAILURE);
	philo_threads(&data);
	pthread_join(*data.philo_t, NULL);
	// destroy_philos(&data);
	return (EXIT_SUCCESS);
}
