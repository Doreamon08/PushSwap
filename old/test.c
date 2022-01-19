#include <stdio.h>
#include <stdlib.h>
#include "lib/libft.h"

int main()
{
	int	*i;

	i = malloc(sizeof(int));
	i[0] = 0;
	if(!i[0])
		printf("lul\n");
}