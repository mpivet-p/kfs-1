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
