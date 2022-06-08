#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include "libc/stdio.h"
#include "gdt/gdt.h"

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.
struct limine_terminal *terminal;

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

void k_write(const char* str, unsigned int charCount)
{
    terminal_request.response->write(terminal, str, charCount);
}

void move_cursor(int x, int y)
{
	printf("\033[%d;%dH", y, x);
}

// The following will be our kernel's entry point.
void _start(void) {
    // Ensure we got a terminal
    if (terminal_request.response == NULL
     || terminal_request.response->terminal_count < 1) {
        done();
    }

    // We should now be able to call the Limine terminal to print out
    // a simple "Hello World" to screen.

    LoadGDT();
    idt_init();

    terminal = terminal_request.response->terminals[0];
    printf("\033[%dm", 36);
    printf("Loaded Successfully!");
    printf("\n");

   //.


    // We're done, just hang...
    done();
}
