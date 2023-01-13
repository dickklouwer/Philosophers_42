/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 13:59:27 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/13 10:53:25 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_checks(t_data *data)
{
	if (data->num_philos < 2)
		return (printf("./philo need atleast 2 philos for the feast\n", EXIT_FAILURE));
	if (data->num_philos > 200)
		return (printf("./philo no more then 200 philos allowed at the feast\n"), EXIT_FAILURE);
	if (data->time_to_die < 0 || data->time_to_sleep < 0 || data->time_to_eat < 0)
		return (printf("./philo time_to_* only 60ms > allowed.\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	chopsticks_init(t_data *data)
{
	int i;

	i = 0;
	data->chopsticks = ft_calloc(data->num_philos, sizeof(pthread_mutex_t));
	if (!data->chopsticks)
		return (printf("Memory allocation failed"), 1);
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->chopsticks[i], NULL))
			return (EXIT_FAILURE);
		i++;
	}
	data->write_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->write_mutex, NULL))
		return (printf("Mutex initialization failed"), 1);
	return (EXIT_SUCCESS);
}

static int    philosophers_init(t_data *data)
{
	int i;

	i = 0;
	data->philo = ft_calloc(data->num_philos + 1, sizeof(t_philo));
	if (!data->philo)
		return (printf("Memory allocation failed"), 1);
	while (i < data->num_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].done = 0;
		data->philo[i].data = data;
		data->philo[i].must_eat = data->n_must_eat;
		data->philo[i].lfork = &data->chopsticks[i];
		data->philo[i].rfork = &data->chopsticks[((i + 1) % data->num_philos)];
		i++;
	}
	return (EXIT_SUCCESS);
}

static int data_init(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		data->n_must_eat = ft_atoi(argv[5]);
		if (data->n_must_eat < 0)
			return(EXIT_FAILURE);
	}
	if (!argv[5])
		data->n_must_eat = -1;
	if (init_checks(data))
		return (EXIT_FAILURE);
	data->philo_t = ft_calloc(1, sizeof(pthread_t));
	if (!data->philo_t)
		return (EXIT_FAILURE);
	if (chopsticks_init(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int parse_input(t_data *data, char **argv, int argc)
{
	int i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		return (printf("./philo: missing arguments"), EXIT_FAILURE);
	} 
	while (i < argc)
	{
		if (only_num(argv[i]))
		{
			return (printf("./philo: only non-negative input allowed\n"), EXIT_FAILURE);
		}
		i++;
	}
	if (data_init(data, argv))
	{
		return (printf("./philo: integer is out of limits\n"), EXIT_FAILURE);
	}
	if (philosophers_init(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
