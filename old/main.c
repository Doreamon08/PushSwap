/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabbie <rabbie@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:43:54 by rabbie            #+#    #+#             */
/*   Updated: 2022/01/19 16:27:06 by rabbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lib/libft.h"

typedef struct s_size
{
	int	*a;
	int	*b;
	int	*fic_a;
	int	*fic_b;
	int	sizea;
	int	sizeb;
	int	flag;
}				t_size;


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

int	*shiftdown(int *a, t_size *size, char c)
{
	int	*ac;
	int	sizeofstack;

	// if (!size->flag)
	// {
	// 	ac = malloc(sizeof(int));
	// 	size->flag = 1;
	// 	return (ac);
	// }
	if (c == 'b')
		sizeofstack = size->sizea;
	else
		sizeofstack = size->sizeb;
	ac = malloc(sizeof(int) * (sizeofstack + 1));
	if (!ac)
		return (a);
	while (sizeofstack)
	{
		ac[sizeofstack] = a[sizeofstack - 1];
		sizeofstack--;
	}
	if (c == 'b')
		size->sizea++;
	else
		size->sizeb++;
	free(a);
	return (ac);
}

int	*delfirst(int *ab, t_size *size, char c)
{
	int	i;
	int	*abc;
	int	sizeofstack;

	i = 0;
	if (!ab)
		return (ab);
	if (c == 'a')
		sizeofstack = size->sizea;
	else
		sizeofstack = size->sizeb;
	abc = malloc(sizeof(int) * (sizeofstack - 1));
	sizeofstack = sizeofstack - 1;
	while (sizeofstack)
	{
		abc[sizeofstack - 1] = ab[sizeofstack];
		sizeofstack--;
	}
	if (c == 'a')
	{
		size->sizea--;
	}
	else
		size->sizeb--;
	free(ab);
	return (abc);
}

int pab(int **a, int **b, t_size *size, char c) //pa and pb
{
	if (c == 'b' && size->sizeb == 0)
		return (0);
	if (c == 'a' && size->sizea == 0)
		return (0);
	*b = shiftdown(*b, size, c);
	*b[0] = *a[0];
	*a = delfirst(*a, size, c);
}

int	rab(int *a, int size)
{
	int	i;
	int	temp;

	i = 0;
	if (!size)
		return (0);
	temp = a[0];
	while (i < size - 1)
	{
		a[i] = a[i + 1];
		i++;
	}
	a[i] = temp;
	return (0);
}

int	rrab(int *ab, int size)
{
	int	i;
	int	temp;
	int	temp2;

	temp = ab[0];
	i = 1;
	if (!size)
		return (0);
	while (i < size)
	{
		if (i == size - 1)
			ab[0] = ab[i];
		temp2 = ab[i];
		ab[i] = temp;
		temp = temp2;
		i++;
	}
	return (0);
}

int printer(int *a, int *b, int sizeAg, t_size *size)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (sizeAg--)
	{
		if (i < size->sizea)
			printf("%d", a[i++]);
		else
			printf("-");
		printf(" | ");
		if (l < size->sizeb)
			printf("%d", b[l++]);
		else
			printf("-");
		printf("\n");
	}
	return (0);
}

int	*sort(int *a, int size)
{
	int	i;
	int	l;
	int	temp;

	i = 1;
	l = 0;
	temp = 0;
	while (l < size)
	{
		while (i < size)
		{
			if (a[i] < a[l])
			{
				temp = a[l];
				a[l] = a[i];
				a[i] = temp;
			}
			i++;
		}
		l++;
		i = l + 1;
	}
	return (a);
}

int	*create_fict();

int main(int ag, char **ac)
{
	int		*a;
	int		*b;
	int		i;
	char	*op;
	t_size	*size;

	size = malloc(sizeof(t_size));
	size->sizea = ag - 1;
	op = malloc(sizeof(char) * 4);
	i = 1;
	size->flag = 0;
	if (ag == 1)
	{
		printf("Error of arguments\n");
		return (1);
	}
	size->a = malloc(sizeof(int) * (ag - 1));
	size->b = malloc(sizeof(int));
	while (i < ag)
	{
		// if (!ft_isdigit(*ac[i]))
		// {
		// 	if (*ac[i] == '-')
		// 	{
		// 		if (!ft_isdigit(*ac[i]))
		// 		{
		// 			printf("Error: argument <%s> not number\n", ac[i]);
		// 			return (1);
		// 		}
		// 	}
		// }
		size->a[i - 1] = chartonum(ac[i]);
		i++;
	}
	i = 0;
	while (1)
	{
		// while (i < ag - 1)
		// {
		// 	printf("%d | %d \n", a[i], b[i]);
		// 	i++;
		// }
		printer(size->a, size->b, ag - 1, size);
		printf("\n");
		printer(sort(a, size->sizea), b, ag - 1, size);
		printf("\n%d - sizea, %d - sizeb\n", size->sizea, size->sizeb);
		printf("%d - score\n", i);
		scanf("%s", op);
		if (op[0] == 's' && op[1] == 'a')//sa
			sab(a);
		else if (op[0] == 's' && op[1] == 'b')//sb
			sab(b);
		else if (op[0] == 's' && op[1] == 's')//ss
			sab(a);
		else if (op[0] == 'p' && op[1] == 'a')//pa
			pab(&b, &a, size, 'b');
		else if (op[0] == 'p' && op[1] == 'b')//pb
			pab(&a, &b, size, 'a');
		else if (op[0] == 'r' && op[1] == 'a')//ra
			rab(a, size->sizea);
		else if (op[0] == 'r' && op[1] == 'b')//rb
			rab(b, size->sizeb);
		else if (op[0] == 'r' && op[1] == 'r' && !op[2])//rr
		{
			rab(a, size->sizea);
			rab(b, size->sizeb);
		}
		else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'a')//rra
			rrab(a, size->sizea);
		else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'b')//rrb
			rrab(b, size->sizeb);
		else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'r')//rrr
		{
			rrab(a, size->sizea);
			rrab(b, size->sizeb);
		}
		else
			printf("incorrect operation\n");
		printf("\n");
		i++;
	}
}
