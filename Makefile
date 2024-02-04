OBJECTS = kernel.o gdt.o port.o loader.o interrupt.o interruptasm.o pic.o io.o \
			ps2_controller.o keyboard_driver.o
CPPFLAGS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -ffreestanding
AFLAGS = --32
LDFLAGS = -melf_i386 -T
QEMUFLAGS = -no-shutdown -cdrom
BOCHSFLAGS = -f bochsrc.txt -q
GRUBCFG = set timeout=0\nset default=0\nmenuentry "My OS" {\nmultiboot /boot/kernel.bin\nboot\n} 
AS = as
CPP = g++
QEMU = qemu-system-x86_64
BOCHS = bochs

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

%.o: %.s
	$(AS) $(AFLAGS) -o $@ $<

kernel.bin: linker.ld $(OBJECTS)
	ld $(LDFLAGS) $< -o $@ $(OBJECTS)

kernel.iso:	kernel.bin
	sudo mkdir -p ~/iso
	sudo mkdir -p ~/iso/boot
	sudo mkdir -p ~/iso/boot/grub
	sudo cp $< -p ~/iso/boot/
	sudo echo -e "$(GRUBCFG)" > ~/iso/boot/grub/grub.cfg
	sudo grub-mkrescue --output=$@ ~/iso

run: kernel.iso
	$(QEMU) $(QEMUFLAGS) $<
	# $(BOCHS) $(BOCHSFLAGS) 

.PHONY: clean
clean:
	rm -rf $(OBJECTS) kernel.bin kernel.iso bochslog.txt

	
