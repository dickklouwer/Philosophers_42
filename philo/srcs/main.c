/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/23 13:27:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/16 15:10:13 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	destroy_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_destroy(&data->chopsticks[i]))
			return (printf("Failed to destroy mutex"), 1);
		i++;
	}
	free(data->chopsticks);
	if (pthread_mutex_destroy(data->write_mutex))
		return (printf("Failed to destroy mutex"), 1);
	free(data->philo);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_data  data;

	if (parse_input(&data, argv, argc))
		return (EXIT_FAILURE);
	philo_threads(&data);
	pthread_join(*data.philo_t, NULL);
	destroy_philos(&data);
	// system("leaks a.out");
	return (EXIT_SUCCESS);
}
