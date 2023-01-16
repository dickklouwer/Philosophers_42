/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 14:59:32 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/05 14:11:41 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <limits.h>

int	error(char *str, int errnum)
{
	printf("%s", str);
	exit (errnum);
}

int	ft_atoi(const char *str)
{
	long long int	res;
	int		min;
	int		i;

	i = 0;
	res = 0;
	min = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			min *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (res > INT_MAX || min == -1)
		return (-1);
	else
		return (min * res);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*u_ptr;
	int				n;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	n = count * size;
	u_ptr = (unsigned char *)ptr;
	while (n > 0)
	{
		n--;
		*u_ptr = 0;
		u_ptr++;
	}
	return (ptr);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// ONLY TESTING //

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr == -2147483648)
		write(fd, "-2147483648", 11);
	else if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-nbr, fd);
	}
	else if (n <= 9)
		ft_putchar_fd(nbr + 48, fd);
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + 48, fd);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

