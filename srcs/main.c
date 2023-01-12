/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/23 13:27:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/12 08:34:53 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



int main(int argc, char **argv)
{
	t_data  data;

	if (parse_input(&data, argv, argc))
		return (EXIT_FAILURE);
	philo_threads(&data);
	pthread_join(*data.philo_t, NULL);
	return (EXIT_SUCCESS);
}
