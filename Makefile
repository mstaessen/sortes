AS = gpasm
CC = sdcc
CFLAGS = -c -mpic16 -p18f97j60 --use-non-free -o $@ $<
LD = sdcc
LDFLAGS = -mpic16 -p18f97j60 --use-non-free \
	-L /usr/local/lib/pic16 \
	-l libio18f97j60.lib \
	-l libdev18f97j60.lib \
	-l libc18f.lib \
	-L include
AR = ar
RM = rm

OBJECTS = Objects/LCDBlocking.o

SDCC_HEADERS = /usr/local/share/sdcc/include/string.h \
   /usr/local/share/sdcc/include/stdlib.h \
   /usr/local/share/sdcc/include/stdio.h \
   /usr/local/share/sdcc/include/stddef.h \
   /usr/local/share/sdcc/include/stdarg.h 

SDCC_PIC16_HEADERS=/usr/local/share/sdcc/include/pic16/pic18f97j60.h

TCPIP_HEADERS = Include/TCPIP_Stack/ETH97J60.h \
   Include/TCPIP_Stack/LCDBlocking.h 

APP_HEADERS = Include/GenericTypeDefs.h \
   Include/Compiler.h \
   Include/HardwareProfile.h 

timer : init Objects/timer.o $(OBJECTS)
	$(LD) $(LDFLAGS) Objects/timer.o $(OBJECTS)
	mv timer.hex build/
	rm -rf *.cod *.hex *.asm *.lst

blinker : init Objects/blinker.o
	$(LD) $(LDFLAGS) Objects/blinker.o
	mv blinker.hex build
	rm -rf *.cod *.hex *.asm *.lst

Objects/%.o : %.c $(SDCC_HEADERS) $(APP_HEADERS)
	$(CC) $(CFLAGS)

Objects/LCDBlocking.o : TCPIP_Stack/LCDBlocking.c $(SDCC_HEADERS) $(APP_HEADERS)
	$(CC) $(CFLAGS) TCPIP_Stack/LCDBlocking.c
    
init : 
	mkdir -p build

clean : 
	$(RM) $(OBJECTS)
