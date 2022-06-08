#include "string.h"

size_t strlen(const char* str)
{
    size_t x = 0;

    while(str[x] != '\0')
        x++;
    
    return x;
}

char* strrev(char* str)
{
    size_t strl = strlen(str);

    for(int i = 0; i < strl / 2; i++)
    {
        char ch = str[i];
        str[i] = str[strl - i - 1];
        str[strl - i - 1] = ch;
    }

    return str;
}
//a

char* itoa(char* str, int m){
    int tmp = 0;
    int f = 0;
    while(m != 0)
    {
        tmp = /*tmp * 10*/ m % 10;
        str[f++] = tmp+'0';

        m /= 10;
    }
    return strrev(str);
}

void memcpy(void* src, void* dst, size_t x)
{
    char* _src = (char*)src;
    char* dest = (char*)dst;

    for(int i=0; i<x; i++)
    {
        dest[i] = _src[i];
    }
}

void *memset(void *s, int c,  unsigned int len)
{
    unsigned char* p=s;
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}//.