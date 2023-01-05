/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/04 15:05:22 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/05 14:22:59 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *philo(void *philosopher)
{
    t_philo *philo;

    philo = (t_philo *)philosopher;
    
    pthread_mutex_lock(&philo->data->chopsticks);
    pthread_mutex_lock(&philo->data->chopsticks[((i + 1) % data->num_philos]);
}

int ft_philosophers(t_data *data)
{
    int i;

    i = 0;
    
    while (i < data->num_philos)
    {
        pthread_create(&data->philo[i]);
        i++;
    }
}