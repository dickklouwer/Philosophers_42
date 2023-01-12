/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/04 14:54:24 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/12 13:52:59 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static u_int64_t	sec_to_millisec(u_int64_t sec)
{
	u_int64_t	millisec;

	millisec = sec * 1000;
	return (millisec);
}

static u_int64_t	microsec_to_millisec(u_int64_t microsec)
{
	u_int64_t	millisec;

	millisec = microsec / 1000;
	return (millisec);
}

u_int64_t	get_current_time(void)
{
	struct timeval	tv;
	u_int64_t		cur_time_ms;

	gettimeofday(&tv, NULL);
	cur_time_ms = (u_int64_t)sec_to_millisec(tv.tv_sec) + \
	microsec_to_millisec(tv.tv_usec);
	return (cur_time_ms);
}

void     p_sleep(t_philo *philo, uint64_t ms, int state)
{
    struct timeval tv1;
    struct timeval tv2;
    
    if (state)
        print_log(philo, state);
    gettimeofday(&tv1, NULL);
    tv1.tv_sec += ms / 1000;
    tv1.tv_usec += (ms % 1000) * 1000;
    if (tv1.tv_usec > 1000000)
    {
        tv1.tv_sec += 1;
        tv1.tv_usec -= 1000000;
    }
    while (1)
    {
        gettimeofday(&tv2, NULL);
        if (tv2.tv_sec > tv1.tv_sec)
			break ;
        if (tv2.tv_sec == tv1.tv_sec && tv2.tv_usec >= tv1.tv_usec)
			break ;
    }
}