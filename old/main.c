/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabbie <rabbie@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:43:54 by rabbie            #+#    #+#             */
/*   Updated: 2022/01/19 21:31:11 by rabbie           ###   ########.fr       */
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
	int	*sorted;
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

int printer(int sizeAg, t_size *size, int *a, int *b)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (sizeAg--)
	{
		if (i < size->sizea)
		{
			printf("%d | %d", a[i], size->fic_a[i]);
			i++;
		}
		else
			printf("- | -");
		printf(" || ");
		if (l < size->sizeb)
		{
			printf("%d | %d", b[l], size->fic_b[l]);
			l++;
		}
		else
			printf("- | -");
		printf("\n");
	}
	return (0);
}

int	*copyar(int	*ar, int size)
{
	int	*copyar;
	int	i;

	copyar = malloc(sizeof(int) * size);
	if (!copyar)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copyar[i] = ar[i];
		i++;
	}
	return (copyar);
}

int	*sort(int *a, int size)
{
	int	i;
	int	l;
	int	temp;
	int	*sorted;

	sorted = copyar(a, size);
	i = 1;
	l = 0;
	temp = 0;
	while (l < size)
	{
		while (i < size)
		{
			if (sorted[i] < sorted[l])
			{
				temp = sorted[l];
				sorted[l] = sorted[i];
				sorted[i] = temp;
			}
			i++;
		}
		l++;
		i = l + 1;
	}
	return (sorted);
}

int	whattheindex(t_size *size, int i)
{
	int	index;

	index = 0;
	while (index < size->sizea)
	{
		if (size->sorted[index] == i)
		{
			return (index);
		}
		index++;
	}
	return (-1);
}

int	*create_fict(t_size *size)
{
	int	*fict_a;
	int	i;
	int	l;

	fict_a = malloc(sizeof(int) * size->sizea);
	if (!fict_a)
		return (NULL);
	i = 0;
	while (i < size->sizea)
	{
		fict_a[i] = whattheindex(size, size->a[i]);
		i++;
	}
	return (fict_a);
}

void complite_sorting(t_size *size, int ag)
{
	int	max_num;
	int	siz;
	int max_bits;
	int	i;
	int	l;
	int	score;

	i = 0;
	l = 0;
	score = 0;
	max_bits = 0;
	siz = size->sizea;
	max_num = size->sizea;
	while ((max_num >> max_bits) != 0)
		max_bits++;
	while (i < max_bits)
	{
		while (l < siz)
		{
			if ((size->fic_a[0] >> i) & 1 == 1)
			{
				// printer(ag, size, size->a, size->b);
				// printf("////////////////////////\n");
				rab(size->a, size->sizea);
				rab(size->fic_a, size->sizea);
				printf ("ra\n");
				score++;
			}
			else
			{
				// printer(ag, size, size->a, size->b);
				// printf("////////////////////////\n");
				pab(&size->a, &size->b, size, 'a');
				size->sizea++;
				size->sizeb--;
				pab(&size->fic_a, &size->fic_b, size, 'a');
				printf ("pb\n");
				score++;
			}
			l++;
		}
		while (size->sizeb != 0)
		{
			// printer(ag, size, size->a, size->b);
			// printf("////////////////////////\n");
			pab(&size->b, &size->a, size, 'b');
			size->sizeb++;
			size->sizea--;
			pab(&size->fic_b, &size->fic_a, size, 'b');
			printf ("pa\n");
			score++;
		}
		i++;
		l = 0;
	}
	printf ("SCORE - %d\n", score);
}

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
	size->sorted = sort(size->a, size->sizea);
	size->fic_a = create_fict(size);
	size->fic_b = malloc(sizeof(int));
	i = 0;
	// while (i < size->sizea)
	// {
	// 	printf("//%d - fic-a //\n", size->fic_a[i++]);
	// }
	// i = 0;
	// while (i < size->sizea)
	// {
	// 	printf("//%d - sorted //\n", size->sorted[i++]);
	// }
	while (1)
	{
		// while (i < ag - 1)
		// {
		// 	printf("%d | %d \n", a[i], b[i]);
		// 	i++;
		// }
		printer(ag - 1, size, size->a, size->b);
		printf("\n");
		printf("\n%d - sizea, %d - sizeb\n", size->sizea, size->sizeb);
		printf("%d - score\n", i);
		complite_sorting(size, ag - 1);
		printf("\n");
		printer(ag - 1, size, size->a, size->b);
		scanf("%s", op);
		if (op[0] == 's' && op[1] == 'a')//sa
			sab(size->a);
		else if (op[0] == 's' && op[1] == 'b')//sb
			sab(size->b);
		else if (op[0] == 's' && op[1] == 's')//ss
		{
			sab(size->a);
			sab(size->b);
		}
		else if (op[0] == 'p' && op[1] == 'a')//pa
			pab(&size->b, &size->a, size, 'b');
		else if (op[0] == 'p' && op[1] == 'b')//pb
			pab(&size->a, &size->b, size, 'a');
		else if (op[0] == 'r' && op[1] == 'a')//ra
			rab(size->a, size->sizea);
		else if (op[0] == 'r' && op[1] == 'b')//rb
			rab(size->b, size->sizeb);
		else if (op[0] == 'r' && op[1] == 'r' && !op[2])//rr
		{
			rab(size->a, size->sizea);
			rab(size->b, size->sizeb);
		}
		else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'a')//rra
			rrab(size->a, size->sizea);
		else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'b')//rrb
			rrab(b, size->sizeb);
		else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'r')//rrr
		{
			rrab(size->a, size->sizea);
			rrab(size->b, size->sizeb);
		}
		else
			printf("incorrect operation\n");
		printf("\n");
		i++;
	}
}
