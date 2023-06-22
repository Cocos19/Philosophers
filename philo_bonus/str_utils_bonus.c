/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:34:52 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/12 11:03:28 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	get_length(int n)
{
	int		result;

	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		result = 2;
		n *= -1;
	}
	else
		result = 1;
	while (n / 10 > 0)
	{
		result++;
		n /= 10;
	}
	return (result);
}

char	*fill_n(char *result, int n, int i)
{
	result[i] = (n % 10) + '0';
	if (n / 10 > 0)
		fill_n(result, (n / 10), (i - 1));
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;

	result = (char *)malloc(sizeof(char) * (get_length(n) + 1));
	if (!result)
		return (NULL);
	i = get_length(n) - 1;
	result[i + 1] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		if (n == -2147483648)
		{
			result[1] = '2';
			n += 2000000000;
		}
		n *= -1;
	}
	return (fill_n(result, n, i));
}

int	ft_atoi(const char *str, int *n)
{
	long int	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (*(str + i) == ' ' || (*(str + i) >= 9 && *(str + i) <= 13))
		i++;
	if (*(str + i) == '-' || *(str + i) == '+')
		if (*(str + i++) == '-')
			sign = -1;
	if (!*(str + i))
		return (1);
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		result = result * 10 + *(str + i++) - '0';
		if (result > INT_MAX && (result * sign != INT_MIN))
			return (1);
	}
	if (*(str + i) && !(*(str + i) >= '0' && *(str + i) <= '9'))
		return (1);
	*n = (int)result;
	return (0);
}
