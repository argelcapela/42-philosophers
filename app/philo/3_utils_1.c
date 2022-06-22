/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:41:05 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/22 10:42:00 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	s;
	int	i;
	int	res;

	s = 1;
	i = 0;
	res = 0;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			s *= -1;
		}
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * s);
}

int	ft_putstr_fd(char *s, int fd)
{
	int		bytes_read;

	bytes_read = 0;
	while (*s)
	{
		bytes_read += write(fd, s, 1);
		s++;
	}
	return (bytes_read);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		mais1;
	char	c;

	mais1 = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n += 1;
			mais1 = 1;
		}
		n *= -1;
		write(fd, "-", 1);
	}
	if (n < 10)
	{
		c = '0' + n;
		write (fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10 + mais1, fd);
	}
}
