/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagevorg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:45:25 by vagevorg          #+#    #+#             */
/*   Updated: 2022/04/20 23:27:02 by vagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countn(int n)
{
	int	count;

	count = 1;
	if (n < 0)
		count++;
	//n = n / 10;
	while (n / 10 != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			nish;
	long int	tiv;
	char		*convert;

	nish = countn(n);
	convert = malloc(nish + 1);
	tiv = n;
	if (convert == 0)
		return (0);
	if ( n < 0)
		tiv = -tiv;
	convert[nish] = '\0';
	while (nish > 1)
	{
		nish--;
		convert[nish] = tiv % 10 + '0';
		tiv = tiv / 10;
	}
	if (n < 0)
		convert[0] = '-';
	else
		convert[0] = tiv % 10 + '0';
	return (convert);
}

int main()
{
	printf("%s",ft_itoa(-255));
}
