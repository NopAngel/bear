

#											_ [ B E A R      |      O S ] _
#
#
# 													-compile: compile files
# 													-iso: compile with grub (for .iso)
# 													-run-iso: run iso
# 													-clean: delete ass files
#
# _ Made by: NopAngel, LICESE: APACHE 2.0








ISO_NAME=BearOS.iso
KERNEL_BIN=kernel

compile:
	nasm -f elf32 kernel.asm -o kasm.o -lm
	gcc -m32 -c kernel.c -o kc.o
	gcc -m32 -c fs/k_printf.c -o k_print.o
	gcc -m32 -c reboot.c -o reboot.o
	gcc -m32 -c shutdown.c -o shutdown.o
	gcc -m32 -c panic/panic.c -o panic.o
	gcc -m32 -c include/drivers/vesa/vesa.c -o vesa.o
	gcc -m32 -c include/itoa.c -o itoa.o
	gcc -m32 -c cpu/get_cpu_info.c -o cpu_info.o
	gcc -m32 -c include/memory/sharedmemory.c -o sharedmemory.o
	gcc -m32 -c include/drivers/mouse/mouse.c -o mouse.o
	
	ld -m elf_i386 -T link.ld -o $(KERNEL_BIN) kasm.o kc.o k_print.o reboot.o shutdown.o panic.o vesa.o itoa.o cpu_info.o sharedmemory.o mouse.o 


#compile:
#	nasm -f elf32 kernel.asm -o kasm.o -lm
#	gcc -m32 -c kernel.c -o kc.o
#	ld -m elf_i386 -T link.ld -o $(KERNEL_BIN) kasm.o kc.o

iso: compile
	mkdir -p iso/boot/grub
	cp $(KERNEL_BIN) iso/boot/
	# echo 'set timeout=5\nset default=0\set gfxpayload=1920x1080\nmenuentry "BearOS" {\n    multiboot /boot/kernel\n    boot\n}' > iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_NAME) iso

run-iso: iso
	qemu-system-i386 -cdrom $(ISO_NAME)

run:
	qemu-system-i386 -kernel ./kernel -vga std

intro:
	g++ ./intro.cxx -o ax && sudo ./ax

clean:
	rm -rf iso
	rm -f kasm.o kc.o $(KERNEL_BIN) $(ISO_NAME)




#
#	set timeout=5
#set default=0
#set gfxpayload=1920x1080
#framebuffer = (uint8_t *)multiboot_info->framebuffer_addr;
#framebuffer_width = multiboot_info->framebuffer_width;
#framebuffer_height = multiboot_info->framebuffer_height;
#framebuffer_pitch = multiboot_info->framebuffer_pitch;
#framebuffer_bpp = multiboot_info->framebuffer_bpp;



#menuentry "BearOS" {
#    multiboot /boot/kernel
#    boot
#}
#
#
