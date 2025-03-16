

#											_ [ B E A R  - GAME     |      O S ] _
#
#
# 													-compile: compile files
# 													-iso: compile with grub (for .iso)
# 													-run-iso: run iso
# 													-clean: delete ass files
#
# _ Made by: NopAngel, LICESE: 








ISO_NAME=BearOS.iso
KERNEL_BIN=kernel

compile:
	nasm -f elf32 kernel.asm -o kasm.o -lm
	gcc -m32 -c kernel.c -o kc.o
	ld -m elf_i386 -T link.ld -o $(KERNEL_BIN) kasm.o kc.o

iso: compile
	mkdir -p iso/boot/grub
	cp $(KERNEL_BIN) iso/boot/
	echo 'set timeout=5\nset default=0\nmenuentry "BearOSGame" {\n    multiboot /boot/kernel\n    boot\n}' > iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_NAME) iso

run-iso: iso
	qemu-system-i386 -cdrom $(ISO_NAME)


clean:
	rm -rf iso
	rm -f kasm.o kc.o $(KERNEL_BIN) $(ISO_NAME)
