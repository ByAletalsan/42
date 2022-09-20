#include <string.h>
#include <stdio.h>
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				res;

	i = 0;
	res = 0;
	if (n == 0)
		return (0);
	while (!res && (s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		res = s1[i] - s2[i];
		if (!res)
			i++;
	}
	if (i < n)
	{
		res = s1[i] - s2[i];
	}
	return (res);
}

int main()
{
	char s[] = "hola mundo que tal estamos";
	char p[] = "hola gente";
	int n = 0;
    printf("FT: %d\nORI: %d\n", ft_strncmp(s, p, n), strncmp(s, p ,n));

    return(0);
}