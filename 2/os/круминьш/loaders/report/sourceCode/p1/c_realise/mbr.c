#define SECTOR_SIZE 512
#define BOOTLOADER_TYPE
#define BOOTLOADER_RUNNING_ADDRESS 0x8000
#define BOOTLOADER_LOAD_ADDRESS 0x8000
#define BOOTLOADER_START_SECTOR 1

asm(".code16gcc\n");

#define __NOINLINE  __attribute__((noinline))
#define __REGPARM   __attribute__ ((regparm(3)))
#define __NORETURN  __attribute__((noreturn))
		
void __NOINLINE __REGPARM print(const char *s) {
	while(*s) {
		asm volatile (
			"movb	$0x0E, %%ah\n"
			"movb	%b0, %%al\n"
			"int	$0x10"
			: 
			: "al"(*s++):"ah","bx");
	}
}

void __NORETURN __attribute__((section("__start"))) main(){
	print("Hello, MBR!\r\n");
	goto *((void *) BOOTLOADER_RUNNING_ADDRESS);
}