/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabbie <rabbie@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:43:54 by rabbie            #+#    #+#             */
/*   Updated: 2022/01/15 00:04:42 by rabbie           ###   ########.fr       */
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

int sab(int *a) //sa and sb
{
	int temp;

	if (!a || !a[1])
		return (0);
	temp = a[0];
	a[0] = a[1];
	a[1] = temp;
	return (0);
}

int *shiftdown(int *a, int size) 
{
	int i;
	int *ac;

	i = 0;
	ac = malloc(sizeof(int) * size);
	if (!ac)
		return (a);
	size--;
	while (size)
	{
		ac[size] = a[size - 1];
		size--;
	}
	free(a);
	return (ac);
}

int *delfirst(int *ab, int size)
{
	int i;
	int *abc;

	i = 0;
	if (!ab)
		return (ab);
	abc = malloc(sizeof(int) * size);
	// ft_memset(abc, 0, sizeof(int) * i);
	size--;
	while (size)
	{
		abc[size - 1] = ab[size];
		size--;
	}
	free(ab);
	return (abc);
}

int pab(int **a, int **b, int size) //pa and pb
{
	if (!**a)
		return (0);
	*b = shiftdown(*b, size);
	*b[0] = *a[0];
	*a = delfirst(*a, size);
}

int	rab(int *a)
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
int	rrab(int *ab)
{
	int	i;
	int	temp;
	int	temp2;

	temp = ab[0];
	i = 1;
	if (!ab)
		return (0);
	while(ab[i])
	{
		if (!ab[i + 1])
			ab[0] = ab[i];
		temp2 = ab[i];
		ab[i] = temp;
		temp = temp2;
		i++;
	}
	return (0);
}
int main(int ag, char **ac)
{
	int	*a;
	int	*b;
	int	i;
	char *op;

	op = malloc(sizeof(char) * 4);
	i = 1;
	if (ag == 1)
	{
		printf("Error of arguments\n");
		return (1);
	}
	a = malloc(sizeof(int) * (ag - 1));
	b = malloc(sizeof(int) * (ag - 1));
	while (i < ag)
	{
		if (!ft_isdigit(*ac[i]))
		{
			printf("Error: argument <%s> not number\n", ac[i]);
			return (1);
		}
		a[i - 1] = chartonum(ac[i]);
		// printf("%d - argument is - %d\n", i, chartonum(ac[i]));
		i++;
	}
	i = 0;
	while (1)
	{
		while (i < ag - 1)
		{
			printf("%d | %d \n", a[i], b[i]);
			i++;
		}
		scanf("%s", op);
		if (op[0] == 's' && op[1] == 'a')//sa
			sab(a);
		else if (op[0] == 's' && op[1] == 'b')//sb
			sab(b);
		else if (op[0] == 's' && op[1] == 's')//ss
			sab(a);
		else if (op[0] == 'p' && op[1] == 'a')//pa
			pab(&b, &a, ag - 1);
		else if (op[0] == 'p' && op[1] == 'b')//pb
			pab(&a, &b, ag - 1);
		else if (op[0] == 'r' && op[1] == 'a')//ra
			rab(a);
		else if (op[0] == 'r' && op[1] == 'b')//rb
			rab(b);
		else if (op[0] == 'r' && op[1] == 'r')//rr
		{
			sab(a);
			sab(b);
		}
		else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'a')//rra
			sab(a);
		else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'b')//rrb
			sab(a);
		else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'r')//rrr
			sab(a);
		else
			printf("incorrect operation");
		i = 0;
	}
}
