COPTS=-march=armv7-a -marm -mno-thumb-interwork -Os -mno-apcs-frame -fomit-frame-pointer -ffunction-sections -fdata-sections

.PHONY: all clean

all: mbrboot.bin

mbrboot.bin : mbrboot.elf
	$(OBJCOPY) -S -R .note.gnu.build-id -O binary mbrboot.elf mbrboot.bin

mbrboot.s : mbrboot.c
	$(CC) -Wall $(COPTS) -S -c mbrboot.c

mbrboot.o : mbrboot.c
	$(CC) -Wall $(COPTS) -c mbrboot.c

mbrboot.elf : mbrboot.o mbrboot.ld
	$(CC) -Wl,--gc-sections -Wl,-static -o mbrboot.elf -nostdlib -Tmbrboot.ld -fno-pic mbrboot.o
	size mbrboot.elf

clean:
	rm -f *.elf *.bin *.o
