#include "libc/stdio.h"
#include "libc/string.h"
char buffer[128];
int bufUsed = 0;

void print_hex_impl(unsigned long long num, int nibbles) { for(int i = nibbles - 1; i >= 0; -- i) putch("0123456789ABCDEF"[(num >> (i*4))&0xF]); }
#define print_hex(num) print_hex_impl((num), sizeof((num)) * 2)
#define print_hex_u64(num) print_hex_impl((num), sizeof((num)) *2)

void putch(char c)
{
    buffer[bufUsed++] = c;
}
//.
void write(const char* str)
{
    k_write(str, strlen(str));
}
void flushBuffer()
{
    memset(buffer, 0, strlen(buffer));
    bufUsed = 0;
}
void PutDecimal(int x)
{
    char strdec[60];
    char* str = itoa(strdec, x);
    for(int i = 0; i < strlen(str); i++)
    {
        putch(str[i]);
    }
}

int printf(const char* fmt, ...)
{
    va_list list;
    va_start(list, fmt);

    for(int i = 0; i < strlen(fmt); i++)
    {
        if(fmt[i] == '%')
        {
            switch(fmt[++i])
            {
                case 'c':
                {
                    int c = va_arg(list, int);
                    putch(c);
                    break;
                }
                case 's':
                {
                    char* str = va_arg(list, char*);
                    for(int i = 0; i < strlen(str); i++)
                    {
                        putch(str[i]);
                    }
                    break;
                }
                case 'd':
                {
                    int dcm = va_arg(list, int);
                    PutDecimal(dcm);
                    break;
                }
                case 'x':
//a
                {
                    int hex = va_arg(list, unsigned int);
               
                    print_hex(hex);
                    break;   
                }

                case 'l':
//a
                {
                    int lhex = va_arg(list, uint64_t);
               
                    print_hex(lhex);
                    break;   
                }

                case '%':
                {
                    putch('%');
                    break; 
                }       
            }
        }
        else
        {
            putch(fmt[i]);
        }
    }
    write(buffer);
    flushBuffer();
    va_end(list);
    return 1;
}