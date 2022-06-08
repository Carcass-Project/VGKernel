#ifndef idt_h_
#define idt_h_

#include <stdint.h>
#include <stddef.h>
#include "libc/stdio.h"
#include "Interrupts/PIC.h"
#include "sched/Timer.h"


typedef struct __attribute__((packed))
{
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;
    uint64_t int_no, error_code, rip, cs, rflags, rsp, ss;
} Registers;

typedef struct  __attribute__((packed)){
   uint16_t offset_1; 
   uint16_t selector; 
   uint8_t  ist;            
   uint8_t  type_attributes; 
   uint16_t offset_2;   
   uint32_t offset_3;  
   uint32_t zero;     
} idtdesc;



typedef struct __attribute__((packed))
{
    uint16_t size;
    uint64_t addr;
} idtr;

static idtdesc entries[256] = {0};
static idtr idtptr = {0};
extern void* isr_stub_table[];

void idt_setdesc(uint64_t vec, void* isr, uint8_t flgs);
void idt_init();
void inthandler(Registers *regs);

#endif