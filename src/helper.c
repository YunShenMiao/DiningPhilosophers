/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:20:52 by jwardeng          #+#    #+#             */
/*   Updated: 2025/02/21 15:45:07 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_threads(t_data **data)
{
	int i;

	i = 1;

	while(i <= (*data)->philo_nbr)
	{
		free((*data)->philo[i].thread);
		i++;
	}
	free((*data)->philo[i].thread);
}

int	ft_strlen(char const *stri)
{
	int	count;

	count = 0;
	while (stri[count] != '\0')
	{
		count++;
	}
	return (count);
}

//copies src string to allocated string 
char	*ft_strdup(const char *src)
{
	int		strl;
	char	*res;
	int		count;

	strl = ft_strlen(src);
	res = malloc((strl + 1) * sizeof(char));
	count = 0;
	if (res == NULL)
		return (NULL);
	while (src[count] != '\0')
	{
		res[count] = src[count];
		count++;
	}
	res[count] = '\0';
	return (res);
}

//converts str to int skipping ws 1+ or -
int	ft_atoi(const char *str)
{
	int	count;
	int	cneg;
	int	res;

	count = 0;
	cneg = 1;
	res = 0;
	while (str[count] == ' ' || str[count] == '\t' || str[count] == '\n'
		|| str[count] == '\v' || str[count] == '\f' || str[count] == '\r')
		count++;
	if (str[count] == '-')
	{
		cneg = -1;
		count++;
	}
	else if (str[count] == '+')
		count++;
	while (str[count] >= '0' && str[count] <= '9')
	{
		res = res * 10 + (str[count] - '0');
		count++;
	}
    if (cneg == -1)
    res = res * cneg;
	return (res);
}

static int	ft_len(int n, int sign)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len + sign);
}

static char	*ft_trans(char *res, int len, int sign, int n)
{
	res[len] = '\0';
	len--;
	while (len >= 0 + sign)
	{
		res[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	if (sign == 1)
		res[0] = '-';
	return (res);
}

// turns int into str, allocates and returns string
char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*res;

	sign = 0;
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		n = -n;
		sign = 1;
	}
	len = ft_len(n, sign);
	res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res = ft_trans(res, len, sign, n);
	return (res);
}
