#ifndef STRING_H
# define STRING_H

# include <stddef.h>

size_t	strlen(const char* str);
void	*memcpy(void *dest, const void *src, size_t n);
char	*strcpy(char *dst, const char *src);
char	*strcat(char *restrict s1, const char *restrict s2);
void	bzero(void *s, size_t n);

#endif
