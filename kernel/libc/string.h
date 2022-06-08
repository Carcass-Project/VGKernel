#ifndef STRING_H
#define STRING_H
#include <stdint.h>
#include <stddef.h>

/* STRING.H FUNCTIONS */
size_t strlen(const char* str);
char* strrev(char* str);
char* itoa(char* buf, int x);

void memcpy(void* src, void* dst, size_t x);
void *memset(void *s, int c, unsigned int len);

//a
#endif