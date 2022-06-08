#include "gdt/gdt.h"
#include <stdint.h>
#include <stddef.h>
#include "libc/stdio.h"

#define PACKED __attribute__((packed))

typedef struct GDTEntry
{
	uint16_t  limit_low;
	uint16_t   base_low;
	uint8_t    base_mid;
	uint8_t      access;
	uint8_t limit_upper : 4;
	uint8_t       flags : 4;
	uint8_t  base_upper;
} PACKED;

typedef struct GDTPointer
{
	uint16_t size;
	uint64_t addr;
} PACKED;

static struct GDTEntry gentries[3];
static uint8_t ent_ptr = 0;
static struct GDTPointer gpointer;

static void GDTInstall()
{
	printf("About to Install GDT");
	__asm__ volatile("lgdt %0\n"
		
		:: "m"(gpointer));
	printf("Did LGDT");
	__asm__ volatile ("call reloadSegments\n");
	printf("Reloaded Segments.");
}

static void GDTEntryNew(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	struct GDTEntry *ent = &gentries[ent_ptr++];

	ent->base_low = base &    0x0000FFFF;
	ent->base_mid = base &   (0x00FF0000) >> 16;
	ent->base_upper = base & (0xFF000000) >> 24;

	ent->access = access;
	ent->flags  =  flags;

	ent->limit_low = limit &    0x0000FFFF;
	ent->limit_upper = limit & (0x000F0000) >> 16;

    printf("Entry: %l", *(uint64_t*)ent);
}
//.
void LoadGDT()
{
	// NULL
	GDTEntryNew(0, 0x0000000000000000 , ACCESS_ATTR_NULL, FLAG_ATTR_NULL);

	// CODE
	uint8_t access = ACCESS_ATTR_CODEDATA | ACCESS_ATTR_PRESENT |
					ACCESS_ATTR_EXEC | ACCESS_ATTR_READABLE;
	GDTEntryNew(0, 0x00af9b000000ffff, access, FLAG_ATTR_GRAN4K | FLAG_ATTR_S64B);

	// DATA
	access = ACCESS_ATTR_CODEDATA | ACCESS_ATTR_PRESENT |
			ACCESS_ATTR_WRITABLE;
	GDTEntryNew(0, 0x00af93000000ffff, access, FLAG_ATTR_GRAN4K | FLAG_ATTR_S32B);

    

	gpointer.addr = (uint64_t)(uintptr_t)gentries;
	gpointer.size = sizeof(gentries) - 1;
	printf("GPointers done\n");
	printf("GPointer: %x\n", gpointer);
	printf("GEntries Table: %x || Size/Count: %d", gentries, sizeof(gentries)/sizeof(struct GDTEntry));
	GDTInstall();
	printf("GDT done");
}