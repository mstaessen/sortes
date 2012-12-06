AS = gpasm
CC = sdcc
CFLAGS= -c -mpic16 -p18f97j60
LD = sdcc
LDFLAGS= -mpic16 -p18f97j60 -L/usr/local/lib/pic16 -llibio18f97j60.lib \
         -llibdev18f97j60.lib -llibc18f.a -L include
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

INCLUDES=-Iinclude -I/usr/local/share/sdcc/include/ -I/usr/local/share/sdcc/include/pic16

main: init obj/main.o obj/lcd.o obj/incl/lcd.o
	$(LD) $(LDFLAGS) obj/main.o obj/lcd.o obj/incl/lcd.o 

init:
	mkdir -p obj/incl

obj/%.o: src/%.c
	@echo "Building object $@"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

obj/incl/lcd.o : lib/LCDBlocking.c
	@echo "Building object $@"
	$(CC) -c -mpic16 -p18f97j60  -o $@ \
              -L/usr/local/lib/pic16  $<

clean : 
	$(RM) -rf obj main.hex main.cod main.lst
