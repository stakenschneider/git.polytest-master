boot: boot.c linker.ld
	@gcc ${CFLAGS} -c -Os -nostdinc -nostdlib -nodefaultlibs -fno-builtin -Wl,--gc-sections -fno-stack-protector -ffreestanding -m32 -Wall -Werror -I. -o boot.o boot.c
	@ld -melf_i386 -static -Tlinker.ld -nostdlib --nmagic -o boot.elf boot.o
	@objcopy -O binary boot.elf boot.MBR
	
clean:
	rm -rf boot.elf boot.MBR boot.o