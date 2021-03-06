AS = gpasm
CC = sdcc
CFLAGS= -c -mpic16 -p18f97j60 --use-non-free
LD = sdcc
LDFLAGS= -mpic16 -p18f97j60 --use-non-free -L/usr/local/lib/pic16 -llibio18f97j60.lib \
         -llibdev18f97j60.lib -llibc18f.lib -L include
AR = ar
RM = rm

SDCC_HEADERS=/usr/local/share/sdcc/include/string.h \
   /usr/local/share/sdcc/include/stdlib.h \
   /usr/local/share/sdcc/include/stdio.h \
   /usr/local/share/sdcc/include/stddef.h \
   /usr/local/share/sdcc/include/stdarg.h 

SDCC_PIC16_HEADERS=/usr/local/share/sdcc/include/pic16/pic18f97j60.h

#TCPIP_HEADERS=   Include/TCPIP_Stack/ETH97J60.h \
#   include/TCPIP_Stack/LCDBlocking.h 
LCD_HEADERS= include/LCDBlocking.h

APP_HEADERS=include/GenericTypeDefs.h \
   include/Compiler.h \
   include/HardwareProfile.h 

INCLUDES=-IInclude -I/usr/local/share/sdcc/include/ -I/usr/local/share/sdcc/include/pic16

main: clock
	
clock: init obj/clock.o obj/time.o obj/incl/lcd.o obj/kernel/sortes.o
	$(LD) $(LDFLAGS) obj/*.o obj/incl/*.o obj/kernel/*.o

interruptcounter: init obj/interruptcounter.o obj/incl/lcd.o
	$(LD) $(LDFLAGS) obj/interruptcounter.o obj/incl/*.o

init:
	mkdir -p obj/incl obj/kernel

obj/%.o: src/%.c
	@echo "Building object $@"
	$(CC) $(CFLAGS) $(INCLUDES) -Ikernel-src/ -o $@ $<

obj/incl/lcd.o : lib/LCDBlocking.c
	@echo "Building object $@"
	$(CC) $(CFLAGS) -o $@ \
              -L/usr/local/lib/pic16  $<

obj/kernel/%.o: kernel-src/%.c
	@echo "Building kernel object $@"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

clean : 
	$(RM) -rf obj *.hex *.cod *.lst
