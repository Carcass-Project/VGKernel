#include <stdint.h>
#include "idt/idt.h"

void k_write(const char* str, unsigned int charCount);
void move_cursor(int x, int y);