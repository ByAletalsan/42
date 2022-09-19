#include <string.h>
#include <stdio.h>
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*string_dst;
	const 	char	*string_src;

	i = 0;
	string_dst = dst;
	string_src = src;
	if (dst == 0)
		return (NULL);
	while (i < n)
	{
		*string_dst = *string_src;
		string_dst += 1;
		string_src += 1;
		i++;
	}
	*string_dst = '\0';
	return (dst);
}
int main()
{
	char n = 'a';
	char p = 'b';
	ft_memcpy(&p, &n, 1);
	printf("%c", p);
}