

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
DISK_IMAGE=fat12.img

compile:
	nasm -f elf32 kernel.asm -o kasm.o
	nasm -f elf32 sound_blaster.s -o sound_blaster.o
	
	
	
	# C++
	g++ -m32 -fno-stack-protector -g -fomit-frame-pointer -fno-exceptions -fno-rtti -c pnp/pnp.cpp -o pnp.o
	g++ -m32 -fno-stack-protector -fno-exceptions -fno-rtti -c ports/serial_ports.cpp -o xq.o
	gcc -m32 -fno-stack-protector -c kernel.c -o kc.o
	gcc -m32 -fno-stack-protector -c fs/k_printf.c -o k_print.o
	gcc -m32 -fno-stack-protector -c reboot.c -o reboot.o
	gcc -m32 -fno-stack-protector -c shutdown.c -o shutdown.o
	gcc -m32 -fno-stack-protector -c panic/panic.c -o panic.o
	gcc -m32 -fno-stack-protector -c include/drivers/vesa/vesa.c -o vesa.o
	gcc -m32 -fno-stack-protector -c include/itoa.c -o itoa.o
	gcc -m32 -fno-stack-protector -c cpu/get_cpu_info.c -o cpu_info.o
	gcc -m32 -fno-stack-protector -c include/memory/sharedmemory.c -o sharedmemory.o
	gcc -m32 -fno-stack-protector -c include/drivers/mouse/mouse.c -o mouse.o 
	gcc -m32 -fno-stack-protector -c fs/k_printf_no_newline.c -o krpp.o # K-PRINTF-NO-NEWLINE <-- fnc.
	gcc -m32 -fno-stack-protector -c include/drivers/ps2/drv.c -o drv.o
	gcc -m32 -fno-stack-protector -c ./rtc.c -o rtc.o
	gcc -m32 -fno-stack-protector -c fs/k_printf_xy.c -o krpzq.o
	ld -m elf_i386 -T link.ld -o $(KERNEL_BIN) kasm.o sound_blaster.o xq.o pnp.o kc.o k_print.o reboot.o shutdown.o drv.o rtc.o panic.o vesa.o itoa.o cpu_info.o sharedmemory.o mouse.o krpp.o krpzq.o
iso: compile
	mkdir -p iso/boot/grub
	cp $(KERNEL_BIN) iso/boot/
	grub-mkrescue -o $(ISO_NAME) iso

fat12:
	nasm -f bin boot.asm -o boot.bin
	dd if=boot.bin of=fat12.img bs=512 count=1 conv=notrunc
	mkfs.fat -F 12 $(DISK_IMAGE)
	mkdir -p mnt
	sudo mount -o loop $(DISK_IMAGE) mnt
	sudo echo "Hi fat12!!" > mnt/gretting.txt
	sudo umount mnt

run-fat12: fat12
	qemu-system-i386 -hda $(DISK_IMAGE)

run-iso: iso
	qemu-system-i386 -cdrom $(ISO_NAME)

run:
	qemu-system-i386  -net nic,model=rtl8139 -net user,hostfwd=tcp::8000-:80 -kernel ./kernel -vga std 

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
