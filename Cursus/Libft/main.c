#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int main()
{
	char v[] = ":sd 1313 1";
	char *x = strdup(v);
	char *y = ft_strdup(v);

	printf("%s\n%s\n", x, y);

	free(x);
	free(y);

    return(0);
}