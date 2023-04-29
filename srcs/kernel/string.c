#include <stddef.h>

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return(len);
}

void	*memcpy(void *dest, const void *src, size_t n)
{
	for (size_t i = 0; i < n; i++)
		((char*)dest)[i] = ((char*)src)[i];
	return (dest);
}

char	*strcpy(char *dst, const char *src)
{
	for (size_t i = 0; src[i] != 0x0; i++)
	{
		dst[i] = src[i];
	}
	return (dst);
}

void	bzero(void *s, size_t n)
{
	for (n; n > 0; --n)
	{
		((char*)s)[n] = 0;
	}
}

char	*strcat(char *restrict s1, const char *restrict s2)
{
	size_t	i = 0;
	size_t	j = 0;

	while (s1[i] != 0x0)
		i++;
	while (s2[j] != 0x0)
	{
		s1[i] = '*';
		//s1[i] = s2[j];
		i++;
		j++;
	}
	return (s1);
}
