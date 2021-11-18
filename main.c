/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabbie <rabbie@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:43:54 by rabbie            #+#    #+#             */
/*   Updated: 2021/11/15 22:01:00 by rabbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lib/libft.h"

int	chartonum(char *ch)
{
	int num;
	int i;
	int sign;

	sign = 1;
	i = 0;
	num = 0;
	if (ch)
		while (ch[i])
		{
			// if (!ft_isdigit(*ch))
			// 	return (0);
			if (ch[i] == '-')
			{
				sign *= -1;
				i++;
			}
			num += (ch[i] - 48) % 10;
			num *= 10;
			i++;
		}
	return (num / 10 * sign);
}

int sab(int *a)
{
	int temp;

	if (!a || !a[1])
		return (0);
	temp = a[0];
	a[0] = a[1];
	a[1] = temp;
	return (0);
}

int *shiftdown(int *a)
{
	int i;
	int *ac;

	i = 0;
	while (a[i])
		a[i++];
	ac = malloc(sizeof(int) * i + 1);
	if (!ac)
		return (a);
	i = 0;
	while (a[i])
	{
		ac[i + 1] = a[i];
		i++;
	}
	free(a);
	return (ac);
}

int *delfirst(int *ab)
{
	int i;
	int *abc;

	i = 0;
	if (!ab)
		return (ab);
	while (ab[i])
		ab[i++];
	abc = malloc(sizeof(int) * i - 1);
	i = 0;
	while (ab[i + 1])
	{
		abc[i] = ab[i + 1];
		i++;
	}
	free(ab);
	return (abc);
}

int pb(int **a, int **b)
{
	int i;

	i = 0;
	*b = shiftdown(*b);
	*b[0] = *a[0];
	*a = delfirst(*a);
}

int	rotate(int *a)
{
	int	i;
	int	temp;

	i = 0;
	if (!a)
		return (0);
	temp = a[0];
	while (a[i + 1])
	{
		a[i] = a[i + 1];
		i++;
	}
	a[i] = temp;
	return (0);
}

int main(int ag, char **ac)
{
	int *a;
	int *b;
	int i;
	int j;

	j = 1;
	i = 0;
	if (ag == 1)
		return (0);
	a = malloc(sizeof(int) * (ag));
	if (!a)
		return (0);
	// b = malloc(sizeof(char) * (ag - 1));
	// if (!b)
	// 	return (0);
	while (j < ag)
		a[i++] = chartonum(ac[j++]);
	i = 0;
	while (i < ag - 1)
		printf("%d\n", a[i++]);
	printf("--------------------\n");
	rotate(a);
	i = 0;
	while (i < ag - 1)
		printf("%d - a\n", a[i++]);
	printf("%d - i, %d - a[i]\n", i, a[i - 1]);
	// printf("%d - a\n", a[0]);
	// printf("%d - a\n", a[1]);
	// printf("%d - a\n", a[2]);
	// printf("%d - a\n", a[3]);
	// printf("%d - a\n", a[4]);
	// printf("%d - a\n", a[5]);
	// printf("---------------\n");	
	// printf("%d - b\n", b[0]);
	// printf("%d - b\n", b[1]);
	// printf("%d - b\n", b[2]);
}