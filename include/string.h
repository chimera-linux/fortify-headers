#ifndef _FORTIFY_STRING_H
#define _FORTIFY_STRING_H

#include_next <string.h>

#if defined(_FORTIFY_SOURCE) && _FORTIFY_SOURCE > 0 && defined(__OPTIMIZE__) && __OPTIMIZE__ > 0

#ifdef __cplusplus
extern "C" {
#endif

#undef memcpy
#undef memmove
#undef memset
#undef strcat
#undef strcpy
#undef strncat
#undef strncpy

__typeof__(memcpy) __memcpy_orig __asm__(__USER_LABEL_PREFIX__ "memcpy");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
void *memcpy(void *dst, const void *src, size_t n)
{
	size_t bos_dst = __builtin_object_size(dst, 0);
	size_t bos_src = __builtin_object_size(src, 0);
	char *d = (char *)dst;
	const char *s = (const char *)src;

	/* trap if pointers are overlapping but not if dst == src.
	 * gcc seems to like to generate code that relies on dst == src */
	if ((d < s && d + n > s) ||
	    (s < d && s + n > d))
		__builtin_trap();
	if (n > bos_dst || n > bos_src)
		__builtin_trap();
	return __memcpy_orig(dst, src, n);
}

__typeof__(memmove) __memmove_orig __asm__(__USER_LABEL_PREFIX__ "memmove");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
void *memmove(void *dst, const void *src, size_t n)
{
	size_t bos_dst = __builtin_object_size(dst, 0);
	size_t bos_src = __builtin_object_size(src, 0);

	if (n > bos_dst || n > bos_src)
		__builtin_trap();
	return __memmove_orig(dst, src, n);
}

__typeof__(memset) __memset_orig __asm__(__USER_LABEL_PREFIX__ "memset");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
void *memset(void *dst, int c, size_t n)
{
	size_t bos = __builtin_object_size(dst, 0);

	if (n > bos)
		__builtin_trap();
	return __memset_orig(dst, c, n);
}

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) \
 || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) \
 || defined(_BSD_SOURCE)
#undef stpcpy
__typeof__(stpcpy) __stpcpy_orig __asm__(__USER_LABEL_PREFIX__ "stpcpy");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
char *stpcpy(char *dst, const char *src)
{
	size_t bos = __builtin_object_size(dst, 0);

	if (strlen(src) + 1 > bos)
		__builtin_trap();
	return __stpcpy_orig(dst, src);
}

#undef stpncpy
__typeof__(stpncpy) __stpncpy_orig __asm__(__USER_LABEL_PREFIX__ "stpncpy");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
char *stpncpy(char *dst, const char *src, size_t n)
{
	size_t bos = __builtin_object_size(dst, 0);

	if (n > bos)
		__builtin_trap();
	return __stpncpy_orig(dst, src, n);
}
#endif

__typeof__(strcat) __strcat_orig __asm__(__USER_LABEL_PREFIX__ "strcat");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
char *strcat(char *dst, const char *src)
{
	size_t bos = __builtin_object_size(dst, 0);

	if (strlen(src) + strlen(dst) + 1 > bos)
		__builtin_trap();
	return __strcat_orig(dst, src);
}

__typeof__(strcpy) __strcpy_orig __asm__(__USER_LABEL_PREFIX__ "strcpy");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
char *strcpy(char *dst, const char *src)
{
	size_t bos = __builtin_object_size(dst, 0);

	if (strlen(src) + 1 > bos)
		__builtin_trap();
	return __strcpy_orig(dst, src);
}

__typeof__(strncat) __strncat_orig __asm__(__USER_LABEL_PREFIX__ "strncat");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
char *strncat(char *dst, const char *src, size_t n)
{
	size_t bos = __builtin_object_size(dst, 0);
	size_t slen, dlen;

	if (n > bos) {
		slen = strlen(src);
		dlen = strlen(dst);
		if (slen > n)
			slen = n;
		if (slen + dlen + 1 > bos)
			__builtin_trap();
	}
	return __strncat_orig(dst, src, n);
}

__typeof__(strncpy) __strncpy_orig __asm__(__USER_LABEL_PREFIX__ "strncpy");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
char *strncpy(char *dst, const char *src, size_t n)
{
	size_t bos = __builtin_object_size(dst, 0);

	if (n > bos)
		__builtin_trap();
	return __strncpy_orig(dst, src, n);
}

#ifdef _GNU_SOURCE
#undef mempcpy
__typeof__(mempcpy) __mempcpy_orig __asm__(__USER_LABEL_PREFIX__ "mempcpy");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
void *mempcpy(void *dst, const void *src, size_t n)
{
	size_t bos_dst = __builtin_object_size(dst, 0);
	size_t bos_src = __builtin_object_size(src, 0);

	if (n > bos_dst || n > bos_src)
		__builtin_trap();
	return __mempcpy_orig(dst, src, n);
}
#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#undef strlcat
#undef strlcpy
__typeof__(strlcat) __strlcat_orig __asm__(__USER_LABEL_PREFIX__ "strlcat");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
size_t strlcat(char *dst, const char *src, size_t n)
{
	size_t bos = __builtin_object_size(dst, 0);

	if (n > bos)
		__builtin_trap();
	return __strlcat_orig(dst, src, n);
}

__typeof__(strlcpy) __strlcpy_orig __asm__(__USER_LABEL_PREFIX__ "strlcpy");
extern __inline __attribute__((__always_inline__,__gnu_inline__,__artificial__))
size_t strlcpy(char *dst, const char *src, size_t n)
{
	size_t bos = __builtin_object_size(dst, 0);

	if (n > bos)
		__builtin_trap();
	return __strlcpy_orig(dst, src, n);
}
#endif

#ifdef __cplusplus
}
#endif

#endif

#endif
