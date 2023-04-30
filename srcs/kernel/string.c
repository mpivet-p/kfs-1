#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str)
{
	size_t len = 0;

	while (str[len] != 0)
		len++;
	return (len);
}

void	*memcpy(void *dest, const void *src, size_t n)
{
	for (size_t i = 0; i < n; i++)
		((char*)dest)[i] = ((char*)src)[i];
	return (dest);
}

char	*strcpy(char *dst, const char *src)
{
	for (size_t i = 0; src[i] != 0; i++)
	{
		dst[i] = src[i];
	}
	return (dst);
}

void	bzero(void *s, size_t n)
{
	char *p = s;

	while (n-- > 0) {
		*p++ = 0;
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
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = 0;
	return (s1);
}

char *itoa_buf(int nbr, char *buf)
{
	uint64_t	length = 1;
	uint64_t	rem;
	size_t		i = 0;

	rem = nbr;
	if (nbr < 0)
	{
		rem = -rem;
		buf[i] = '-';
		i++;
	}
	while (length * 10 < rem)
		length *= 10;
	while (length > 0)
	{
		buf[i] = rem / length + '0';
		rem = rem % length;
		length /= 10;
		i++;
	}
	buf[i] = 0;
	return (buf);
}

char *itoa_base_buf(uint32_t nbr, int base, char *buf)
{
	uint64_t	length = 1;
	size_t		i = 0;

	while (length * base < nbr)
		length *= base;
	if (base == nbr)
		length *= base;
	while (length > 0)
	{
		buf[i] = "0123456789abcdef"[nbr / length];
		nbr = nbr % length;
		length /= base;
		i++;
	}
	buf[i] = 0;
	return (buf);
}
