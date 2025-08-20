#
#
#											_ [ B E A R      |      O S ] _
#
#
#  Made by: NopAngel
#  LICESE: APACHE 2.0
#
#



ISO_NAME=BearOS.iso
KERNEL_BIN=kernel
DISK_IMAGE=fat12.img
PY=python3
CC=gcc
GPP=g++
NSM=nasm
FLAGC=-m32 -fno-stack-protector -c
LDFLAG=-m elf_i386 -T link.ld -o $(KERNEL_BIN)
LDPATH=kasm.o sound_blaster.o xq.o i2c.o i3c.o uptime.o xen.o delay.o get_sys_time.o stats.o nvmem.o atm.o ata.o bus.o cache.o accel.o gettime.o clear_screen.o memfs.o uname.o wmsg.o crw.o textdraw.o pnp.o kc.o  k_print.o notify.o reboot.o module.o shutdown.o drv.o rtc.o panic.o vesa.o itoa.o cpu_info.o sharedmemory.o mouse.o krpp.o krpzq.o globalll.o

VG ?= std
NET ?= user
MEM ?= 256M




GPP_FLAGS_EXCEP=-m32 -fno-stack-protector -g -fomit-frame-pointer -fno-exceptions -fno-rtti -c
GPP_FLAGS_RTTI=-m32 -fno-stack-protector -fno-exceptions -fno-rtti -c


GRUB_FODLER=./iso/boot/grub



compile: 
	$(NSM) -f elf32 kernel.asm -o kasm.o
	$(NSM) -f elf32 sound_blaster.s -o sound_blaster.o
	
	
	
	# C++
	$(GPP) $(GPP_FLAGS_EXCEP) pnp/pnp.cpp -o pnp.o
	$(GPP) $(GPP_FLAGS_RTTI) ports/serial_ports.cpp -o xq.o
	
	$(CC) $(FLAGC) kernel.c -o kc.o
	$(CC) $(FLAGC) fs/text_draw.c -o textdraw.o
	$(CC) $(FLAGC) include/drivers/atm/atm.c -o atm.o
	$(CC) $(FLAGC) include/drivers/ata/ata.c -o ata.o
	$(CC) $(FLAGC) include/drivers/cache/cache.c -o cache.o
	$(CC) $(FLAGC) include/stats/stats.c -o stats.o
	$(CC) $(FLAGC) include/drivers/bus/bus.c -o bus.o
	$(CC) $(FLAGC) fs/clear_screen.c -o clear_screen.o
	$(CC) $(FLAGC) include/drivers/nvmem/nvmem.c -o nvmem.o
	$(CC) $(FLAGC) fs/k_printf.c -o k_print.o
	$(CC) $(FLAGC) include/wlcm/wmsg.c -o wmsg.o
	$(CC) $(FLAGC) include/drivers/xen/xen.c -o xen.o
	$(CC) $(FLAGC) include/bear/module.c -o module.o
	$(CC) $(FLAGC) include/time/get_time.c -o gettime.o
	$(CC) $(FLAGC) include/bear/notify/notification_system.c -o notify.o
	$(CC) $(FLAGC) include/wlcm/crw.c -o crw.o
	$(CC) $(FLAGC) include/delay/delay.c -o delay.o
	$(CC) $(FLAGC) include/get_sys_time.c -o get_sys_time.o
	$(CC) $(FLAGC) include/drivers/accel/accel.c -o accel.o
	$(CC) $(FLAGC) apm/reboot.c -o reboot.o
	$(CC) $(FLAGC) include/uname.c -o uname.o
	$(CC) $(FLAGC) include/time/uptime.c -o uptime.o
	$(CC) $(FLAGC) include/sys/shutdown.c -o shutdown.o
	$(CC) $(FLAGC) panic/panic.c -o panic.o
	$(CC) $(FLAGC) include/drivers/vesa/vesa.c -o vesa.o
	$(CC) $(FLAGC) include/memfs/memfs.c -o memfs.o
	$(CC) $(FLAGC) include/itoa.c -o itoa.o
	$(CC) $(FLAGC) cpu/get_cpu_info.c -o cpu_info.o
	$(CC) $(FLAGC) include/memory/sharedmemory.c -o sharedmemory.o
	$(CC) $(FLAGC) include/drivers/mouse/mouse.c -o mouse.o 
	$(CC) $(FLAGC) fs/k_printf_no_newline.c -o krpp.o # K-PRINTF-NO-NEWLINE <-- fnc.
	$(CC) $(FLAGC) include/drivers/ps2/drv.c -o drv.o
	$(CC) $(FLAGC) ./rtc.c -o rtc.o
	$(CC) $(FLAGC) fs/k_printf_xy.c -o krpzq.o
	$(CC) $(FLAGC) include/drivers/i3c/i3c.c i3c.o
	$(CC) $(FLAGC) include/drivers/i2c/i2c.c i2c.o
	$(CC) $(FLAGC) include/io/global.c -o globalll.o
	ld $(LDFLAG) $(LDPATH)




iso: compile
	mkdir -p $(GRUB_FODLER)
	cp $(KERNEL_BIN) ./iso/boot/
	grub-mkrescue -o $(ISO_NAME) iso

run-iso: iso
	qemu-system-i386 -cdrom $(ISO_NAME)

FLAGS_QEMU=-net nic,model=rtl8139 -net user,hostfwd=tcp::8000-:80 -kernel ./kernel -vga std 

run:

	qemu-system-i386  $(FLAGS_QEMU)

clean:
	rm -rf iso
	rm -f kasm.o kc.o $(KERNEL_BIN) $(ISO_NAME)

menuinstall:
	$(PY) ./scripts/menuinstall.py

rm_q: # remove all files (.iso, .o)
	@rm -rf *.o *.iso *.img kernel kernel.elf *.tmp 
	@echo "Makefile> Deleted files trash!"



test:
	@echo "Test for bearOS!"
	@./scripts/rq_test.sh



rebuild: rm_q
	@make compile
	@echo "Makefile> Rebuilding, complete!"


recompiled:
	@echo "🚀 Started bearOS with VGA='$(VG)', NET='$(NET)', MEM='$(MEM)'"
	@qemu-system-x86_64 \
        -kernel bin/bearOS.elf \
        -vga $(VG) \
        -net nic -net $(NET) \
        -m $(MEM)


gdb: compile
	gdb ./kernel



ifndef MEM
	MEM := 512M
endif

ifndef CC
	CC := gcc
endif

ifndef PY
	PY := python
endif





#										Test
#	set timeout=5
#set default=0
#set gfxpayload=1920x1080
#framebuffer = (uint8_t *)multiboot_info->framebuffer_addr; <- NOT USE
#framebuffer_width = multiboot_info->framebuffer_width; <- NOT USE
#framebuffer_height = multiboot_info->framebuffer_height; <- NOT USE
#framebuffer_pitch = multiboot_info->framebuffer_pitch; <- NOT USE
#framebuffer_bpp = multiboot_info->framebuffer_bpp; <- NOT USE



#menuentry "BearOS" {
#    multiboot /boot/kernel
#    boot
#}

	



config:
	$(PY) ./scripts/menuconfig.py




# 🐻 Lista de módulos disponibles
MODULES := SOUND_BLASTER VESA MOUSE_PS2 ACCELEROMETER

# 🐾 Ruta base de drivers
DRIVER_PATH := include/drivers

# 🧠 Compilador y flags
CC := gcc
FLAGC := -m32 -ffreestanding -Wall

# 🛠 Macro para compilar si está habilitado
define compile_if_enabled
ifeq ($(CONFIG_$(1)),y)
    @echo "🔧 Compilando $(1)..."
    $(CC) $(FLAGC) $(DRIVER_PATH)/$(call path_for,$(1)) -o $(call obj_for,$(1))
endif
endef

# 🎯 Funciones auxiliares para rutas
path_for = $(shell echo $(1) | tr A-Z a-z)/$(shell echo $(1) | tr A-Z a-z).c
obj_for = $(shell echo $(1) | tr A-Z a-z).o

# 🧩 Evaluar cada módulo
$(foreach mod,$(MODULES),$(eval $(call compile_if_enabled,$(mod))))

