;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.2.0 #8008 (Jul  6 2012) (Mac OS X i386)
; This file was generated Fri Jan  4 03:09:40 2013
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------
	list	p=18f97j60

	radix dec

;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_ticks
	global	_LCDDisplay
	global	_interruptServiceRoutine
	global	_main

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	__gptrget1
	extern	__gptrput1
	extern	_EBSTCONbits
	extern	_MISTATbits
	extern	_EFLOCONbits
	extern	_MACON1bits
	extern	_MACON2bits
	extern	_MACON3bits
	extern	_MACON4bits
	extern	_MACLCON1bits
	extern	_MACLCON2bits
	extern	_MICONbits
	extern	_MICMDbits
	extern	_EWOLIEbits
	extern	_EWOLIRbits
	extern	_ERXFCONbits
	extern	_EIEbits
	extern	_ESTATbits
	extern	_ECON2bits
	extern	_EIRbits
	extern	_EDATAbits
	extern	_SSP2CON2bits
	extern	_SSP2CON1bits
	extern	_SSP2STATbits
	extern	_ECCP2DELbits
	extern	_ECCP2ASbits
	extern	_ECCP3DELbits
	extern	_ECCP3ASbits
	extern	_RCSTA2bits
	extern	_TXSTA2bits
	extern	_CCP5CONbits
	extern	_CCP4CONbits
	extern	_T4CONbits
	extern	_ECCP1DELbits
	extern	_BAUDCON2bits
	extern	_BAUDCTL2bits
	extern	_BAUDCONbits
	extern	_BAUDCON1bits
	extern	_BAUDCTLbits
	extern	_BAUDCTL1bits
	extern	_PORTAbits
	extern	_PORTBbits
	extern	_PORTCbits
	extern	_PORTDbits
	extern	_PORTEbits
	extern	_PORTFbits
	extern	_PORTGbits
	extern	_PORTHbits
	extern	_PORTJbits
	extern	_LATAbits
	extern	_LATBbits
	extern	_LATCbits
	extern	_LATDbits
	extern	_LATEbits
	extern	_LATFbits
	extern	_LATGbits
	extern	_LATHbits
	extern	_LATJbits
	extern	_DDRAbits
	extern	_TRISAbits
	extern	_DDRBbits
	extern	_TRISBbits
	extern	_DDRCbits
	extern	_TRISCbits
	extern	_DDRDbits
	extern	_TRISDbits
	extern	_DDREbits
	extern	_TRISEbits
	extern	_DDRFbits
	extern	_TRISFbits
	extern	_DDRGbits
	extern	_TRISGbits
	extern	_DDRHbits
	extern	_TRISHbits
	extern	_DDRJbits
	extern	_TRISJbits
	extern	_OSCTUNEbits
	extern	_MEMCONbits
	extern	_PIE1bits
	extern	_PIR1bits
	extern	_IPR1bits
	extern	_PIE2bits
	extern	_PIR2bits
	extern	_IPR2bits
	extern	_PIE3bits
	extern	_PIR3bits
	extern	_IPR3bits
	extern	_EECON1bits
	extern	_RCSTAbits
	extern	_RCSTA1bits
	extern	_TXSTAbits
	extern	_TXSTA1bits
	extern	_PSPCONbits
	extern	_T3CONbits
	extern	_CMCONbits
	extern	_CVRCONbits
	extern	_ECCP1ASbits
	extern	_CCP3CONbits
	extern	_ECCP3CONbits
	extern	_CCP2CONbits
	extern	_ECCP2CONbits
	extern	_CCP1CONbits
	extern	_ECCP1CONbits
	extern	_ADCON2bits
	extern	_ADCON1bits
	extern	_ADCON0bits
	extern	_SSP1CON2bits
	extern	_SSPCON2bits
	extern	_SSP1CON1bits
	extern	_SSPCON1bits
	extern	_SSP1STATbits
	extern	_SSPSTATbits
	extern	_T2CONbits
	extern	_T1CONbits
	extern	_RCONbits
	extern	_WDTCONbits
	extern	_ECON1bits
	extern	_OSCCONbits
	extern	_T0CONbits
	extern	_STATUSbits
	extern	_INTCON3bits
	extern	_INTCON2bits
	extern	_INTCONbits
	extern	_STKPTRbits
	extern	_stdin
	extern	_stdout
	extern	_LCDText
	extern	_MAADR5
	extern	_MAADR6
	extern	_MAADR3
	extern	_MAADR4
	extern	_MAADR1
	extern	_MAADR2
	extern	_EBSTSD
	extern	_EBSTCON
	extern	_EBSTCS
	extern	_EBSTCSL
	extern	_EBSTCSH
	extern	_MISTAT
	extern	_EFLOCON
	extern	_EPAUS
	extern	_EPAUSL
	extern	_EPAUSH
	extern	_MACON1
	extern	_MACON2
	extern	_MACON3
	extern	_MACON4
	extern	_MABBIPG
	extern	_MAIPG
	extern	_MAIPGL
	extern	_MAIPGH
	extern	_MACLCON1
	extern	_MACLCON2
	extern	_MAMXFL
	extern	_MAMXFLL
	extern	_MAMXFLH
	extern	_MICON
	extern	_MICMD
	extern	_MIREGADR
	extern	_MIWR
	extern	_MIWRL
	extern	_MIWRH
	extern	_MIRD
	extern	_MIRDL
	extern	_MIRDH
	extern	_EHT0
	extern	_EHT1
	extern	_EHT2
	extern	_EHT3
	extern	_EHT4
	extern	_EHT5
	extern	_EHT6
	extern	_EHT7
	extern	_EPMM0
	extern	_EPMM1
	extern	_EPMM2
	extern	_EPMM3
	extern	_EPMM4
	extern	_EPMM5
	extern	_EPMM6
	extern	_EPMM7
	extern	_EPMCS
	extern	_EPMCSL
	extern	_EPMCSH
	extern	_EPMO
	extern	_EPMOL
	extern	_EPMOH
	extern	_EWOLIE
	extern	_EWOLIR
	extern	_ERXFCON
	extern	_EPKTCNT
	extern	_EWRPT
	extern	_EWRPTL
	extern	_EWRPTH
	extern	_ETXST
	extern	_ETXSTL
	extern	_ETXSTH
	extern	_ETXND
	extern	_ETXNDL
	extern	_ETXNDH
	extern	_ERXST
	extern	_ERXSTL
	extern	_ERXSTH
	extern	_ERXND
	extern	_ERXNDL
	extern	_ERXNDH
	extern	_ERXRDPT
	extern	_ERXRDPTL
	extern	_ERXRDPTH
	extern	_ERXWRPT
	extern	_ERXWRPTL
	extern	_ERXWRPTH
	extern	_EDMAST
	extern	_EDMASTL
	extern	_EDMASTH
	extern	_EDMAND
	extern	_EDMANDL
	extern	_EDMANDH
	extern	_EDMADST
	extern	_EDMADSTL
	extern	_EDMADSTH
	extern	_EDMACS
	extern	_EDMACSL
	extern	_EDMACSH
	extern	_EIE
	extern	_ESTAT
	extern	_ECON2
	extern	_EIR
	extern	_EDATA
	extern	_SSP2CON2
	extern	_SSP2CON1
	extern	_SSP2STAT
	extern	_SSP2ADD
	extern	_SSP2BUF
	extern	_ECCP2DEL
	extern	_ECCP2AS
	extern	_ECCP3DEL
	extern	_ECCP3AS
	extern	_RCSTA2
	extern	_TXSTA2
	extern	_TXREG2
	extern	_RCREG2
	extern	_SPBRG2
	extern	_CCP5CON
	extern	_CCPR5
	extern	_CCPR5L
	extern	_CCPR5H
	extern	_CCP4CON
	extern	_CCPR4
	extern	_CCPR4L
	extern	_CCPR4H
	extern	_T4CON
	extern	_PR4
	extern	_TMR4
	extern	_ECCP1DEL
	extern	_ERDPT
	extern	_ERDPTL
	extern	_ERDPTH
	extern	_BAUDCON2
	extern	_BAUDCTL2
	extern	_SPBRGH2
	extern	_BAUDCON
	extern	_BAUDCON1
	extern	_BAUDCTL
	extern	_BAUDCTL1
	extern	_SPBRGH
	extern	_SPBRGH1
	extern	_PORTA
	extern	_PORTB
	extern	_PORTC
	extern	_PORTD
	extern	_PORTE
	extern	_PORTF
	extern	_PORTG
	extern	_PORTH
	extern	_PORTJ
	extern	_LATA
	extern	_LATB
	extern	_LATC
	extern	_LATD
	extern	_LATE
	extern	_LATF
	extern	_LATG
	extern	_LATH
	extern	_LATJ
	extern	_DDRA
	extern	_TRISA
	extern	_DDRB
	extern	_TRISB
	extern	_DDRC
	extern	_TRISC
	extern	_DDRD
	extern	_TRISD
	extern	_DDRE
	extern	_TRISE
	extern	_DDRF
	extern	_TRISF
	extern	_DDRG
	extern	_TRISG
	extern	_DDRH
	extern	_TRISH
	extern	_DDRJ
	extern	_TRISJ
	extern	_OSCTUNE
	extern	_MEMCON
	extern	_PIE1
	extern	_PIR1
	extern	_IPR1
	extern	_PIE2
	extern	_PIR2
	extern	_IPR2
	extern	_PIE3
	extern	_PIR3
	extern	_IPR3
	extern	_EECON1
	extern	_EECON2
	extern	_RCSTA
	extern	_RCSTA1
	extern	_TXSTA
	extern	_TXSTA1
	extern	_TXREG
	extern	_TXREG1
	extern	_RCREG
	extern	_RCREG1
	extern	_SPBRG
	extern	_SPBRG1
	extern	_PSPCON
	extern	_T3CON
	extern	_TMR3L
	extern	_TMR3H
	extern	_CMCON
	extern	_CVRCON
	extern	_ECCP1AS
	extern	_CCP3CON
	extern	_ECCP3CON
	extern	_CCPR3
	extern	_CCPR3L
	extern	_CCPR3H
	extern	_CCP2CON
	extern	_ECCP2CON
	extern	_CCPR2
	extern	_CCPR2L
	extern	_CCPR2H
	extern	_CCP1CON
	extern	_ECCP1CON
	extern	_CCPR1
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_ADCON2
	extern	_ADCON1
	extern	_ADCON0
	extern	_ADRES
	extern	_ADRESL
	extern	_ADRESH
	extern	_SSP1CON2
	extern	_SSPCON2
	extern	_SSP1CON1
	extern	_SSPCON1
	extern	_SSP1STAT
	extern	_SSPSTAT
	extern	_SSP1ADD
	extern	_SSPADD
	extern	_SSP1BUF
	extern	_SSPBUF
	extern	_T2CON
	extern	_PR2
	extern	_TMR2
	extern	_T1CON
	extern	_TMR1L
	extern	_TMR1H
	extern	_RCON
	extern	_WDTCON
	extern	_ECON1
	extern	_OSCCON
	extern	_T0CON
	extern	_TMR0L
	extern	_TMR0H
	extern	_STATUS
	extern	_FSR2L
	extern	_FSR2H
	extern	_PLUSW2
	extern	_PREINC2
	extern	_POSTDEC2
	extern	_POSTINC2
	extern	_INDF2
	extern	_BSR
	extern	_FSR1L
	extern	_FSR1H
	extern	_PLUSW1
	extern	_PREINC1
	extern	_POSTDEC1
	extern	_POSTINC1
	extern	_INDF1
	extern	_WREG
	extern	_FSR0L
	extern	_FSR0H
	extern	_PLUSW0
	extern	_PREINC0
	extern	_POSTDEC0
	extern	_POSTINC0
	extern	_INDF0
	extern	_INTCON3
	extern	_INTCON2
	extern	_INTCON
	extern	_PROD
	extern	_PRODL
	extern	_PRODH
	extern	_TABLAT
	extern	_TBLPTR
	extern	_TBLPTRL
	extern	_TBLPTRH
	extern	_TBLPTRU
	extern	_PC
	extern	_PCL
	extern	_PCLATH
	extern	_PCLATU
	extern	_STKPTR
	extern	_TOS
	extern	_TOSL
	extern	_TOSH
	extern	_TOSU
	extern	_sprintf
	extern	_strlen
	extern	_LCDInit
	extern	_LCDUpdate

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
PCLATH	equ	0xffa
PCLATU	equ	0xffb
WREG	equ	0xfe8
BSR	equ	0xfe0
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
INDF0	equ	0xfef
POSTINC0	equ	0xfee
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3
PRODH	equ	0xff4


	idata
_ticks	db	0x00, 0x00, 0x00, 0x00


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1
r0x05	res	1
r0x06	res	1
r0x07	res	1
r0x08	res	1
r0x09	res	1

udata_timer_0	udata
_interruptServiceRoutine_str_3_67	res	33

;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; ; Starting pCode block for absolute section
; ;-----------------------------------------
S_timer_ivec_0x1_interruptServiceRoutine	code	0X000008
ivec_0x1_interruptServiceRoutine:
	GOTO	_interruptServiceRoutine

; I code from now on!
; ; Starting pCode block
S_timer__main	code
_main:
;	.line	79; timer.c	INTCONbits.GIE = 1;
	BSF	_INTCONbits, 7
;	.line	80; timer.c	INTCONbits.PEIE = 1;
	BSF	_INTCONbits, 6
;	.line	82; timer.c	LED0_TRIS = 0;
	BCF	_TRISJbits, 0
;	.line	83; timer.c	LED0_IO = 0;
	BCF	_LATJbits, 0
;	.line	86; timer.c	T0CONbits.TMR0ON = 0;
	BCF	_T0CONbits, 7
;	.line	87; timer.c	T1CONbits.TMR1ON = 0;
	BCF	_T1CONbits, 0
;	.line	91; timer.c	TMR0H = 0x00000000;
	CLRF	_TMR0H
;	.line	92; timer.c	TMR0L = 0x00000000;
	CLRF	_TMR0L
;	.line	94; timer.c	T0CONbits.T08BIT = 1;
	BSF	_T0CONbits, 6
;	.line	96; timer.c	T0CONbits.T0CS = 0;
	BCF	_T0CONbits, 5
;	.line	98; timer.c	T0CONbits.PSA = 1;
	BSF	_T0CONbits, 3
;	.line	100; timer.c	INTCONbits.TMR0IE = 1;
	BSF	_INTCONbits, 5
;	.line	104; timer.c	T1CONbits.RD16 = 1;
	BSF	_T1CONbits, 7
;	.line	108; timer.c	TMR1H = 0x00000000;
	CLRF	_TMR1H
;	.line	109; timer.c	TMR1L = 0x00000000;
	CLRF	_TMR1L
;	.line	111; timer.c	T1CONbits.T1CKPS0 = 0;
	BCF	_T1CONbits, 4
;	.line	112; timer.c	T1CONbits.T1CKPS1 = 0;
	BCF	_T1CONbits, 5
;	.line	114; timer.c	T1CONbits.T1OSCEN = 1;
	BSF	_T1CONbits, 3
;	.line	116; timer.c	T1CONbits.T1SYNC = 1;
	BSF	_T1CONbits, 2
;	.line	118; timer.c	T1CONbits.TMR1CS = 1;
	BSF	_T1CONbits, 1
;	.line	120; timer.c	PIE1bits.TMR1IE = 1;
	BSF	_PIE1bits, 0
;	.line	124; timer.c	LCDInit(); 
	CALL	_LCDInit
;	.line	126; timer.c	LED3_TRIS = 0;
	BCF	_TRISGbits, 5
;	.line	127; timer.c	LED3_IO = 1;
	BSF	_PORTGbits, 5
;	.line	130; timer.c	T1CONbits.TMR1ON = 1;
	BSF	_T1CONbits, 0
_00149_DS_:
;	.line	133; timer.c	while(1);
	BRA	_00149_DS_
	RETURN	

; ; Starting pCode block
S_timer__interruptServiceRoutine	code
_interruptServiceRoutine:
;	.line	42; timer.c	void interruptServiceRoutine (void) __interrupt(1)
	MOVFF	STATUS, POSTDEC1
	MOVFF	BSR, POSTDEC1
	MOVWF	POSTDEC1
	MOVFF	PRODL, POSTDEC1
	MOVFF	PRODH, POSTDEC1
	MOVFF	FSR0L, POSTDEC1
	MOVFF	FSR0H, POSTDEC1
	MOVFF	PCLATH, POSTDEC1
	MOVFF	PCLATU, POSTDEC1
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
;	.line	45; timer.c	if (PIR1bits.TMR1IF) {
	BTFSS	_PIR1bits, 0
	BRA	_00129_DS_
;	.line	47; timer.c	T0CONbits.TMR0ON ^= 1;
	CLRF	r0x00
	BTFSC	_T0CONbits, 7
	INCF	r0x00, F
	BTG	r0x00, 0
	MOVF	r0x00, W
	ANDLW	0x01
	RRNCF	WREG, W
	MOVWF	PRODH
	MOVF	_T0CONbits, W
	ANDLW	0x7f
	IORWF	PRODH, W
	MOVWF	_T0CONbits
;	.line	48; timer.c	LED0_IO ^= 1;
	CLRF	r0x00
	BTFSC	_LATJbits, 0
	INCF	r0x00, F
	BTG	r0x00, 0
	MOVF	r0x00, W
	ANDLW	0x01
	MOVWF	PRODH
	MOVF	_LATJbits, W
	ANDLW	0xfe
	IORWF	PRODH, W
	MOVWF	_LATJbits
;	.line	51; timer.c	if (!T0CONbits.TMR0ON) {
	BTFSC	_T0CONbits, 7
	BRA	_00127_DS_
;	.line	52; timer.c	unsigned short remainder = *(unsigned short *)(&TMR0L);
	MOVLW	LOW(_TMR0L)
	MOVWF	r0x00
	MOVLW	HIGH(_TMR0L)
	MOVWF	r0x01
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	POSTINC0, r0x00
	MOVFF	INDF0, r0x01
;	.line	56; timer.c	sprintf(str, "Elapsed ticks:  %lu + %hu", ticks, remainder);
	MOVLW	UPPER(__str_0)
	MOVWF	r0x04
	MOVLW	HIGH(__str_0)
	MOVWF	r0x03
	MOVLW	LOW(__str_0)
	MOVWF	r0x02
	MOVLW	HIGH(_interruptServiceRoutine_str_3_67)
	MOVWF	r0x06
	MOVLW	LOW(_interruptServiceRoutine_str_3_67)
	MOVWF	r0x05
	MOVLW	0x80
	MOVWF	r0x07
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	BANKSEL	(_ticks + 3)
	MOVF	(_ticks + 3), W, B
	MOVWF	POSTDEC1
	BANKSEL	(_ticks + 2)
	MOVF	(_ticks + 2), W, B
	MOVWF	POSTDEC1
	BANKSEL	(_ticks + 1)
	MOVF	(_ticks + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_ticks
	MOVF	_ticks, W, B
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	MOVF	r0x06, W
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	CALL	_sprintf
	MOVLW	0x0c
	ADDWF	FSR1L, F
;	.line	57; timer.c	LCDDisplay(str, 0);
	MOVLW	HIGH(_interruptServiceRoutine_str_3_67)
	MOVWF	r0x01
	MOVLW	LOW(_interruptServiceRoutine_str_3_67)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_LCDDisplay
	MOVLW	0x04
	ADDWF	FSR1L, F
;	.line	60; timer.c	T1CONbits.TMR1ON = 0;
	BCF	_T1CONbits, 0
_00127_DS_:
;	.line	64; timer.c	PIR1bits.TMR1IF = 0;
	BCF	_PIR1bits, 0
_00129_DS_:
;	.line	68; timer.c	if (INTCONbits.TMR0IF == 1) {
	CLRF	r0x00
	BTFSC	_INTCONbits, 2
	INCF	r0x00, F
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00132_DS_
_00143_DS_:
	BANKSEL	(_ticks + 1)
;	.line	69; timer.c	ticks += 256;
	INCF	(_ticks + 1), F, B
	MOVLW	0x00
	BANKSEL	(_ticks + 2)
	ADDWFC	(_ticks + 2), F, B
	BANKSEL	(_ticks + 3)
	ADDWFC	(_ticks + 3), F, B
;	.line	71; timer.c	INTCONbits.TMR0IF = 0;
	BCF	_INTCONbits, 2
_00132_DS_:
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	MOVFF	PREINC1, PCLATU
	MOVFF	PREINC1, PCLATH
	MOVFF	PREINC1, FSR0H
	MOVFF	PREINC1, FSR0L
	MOVFF	PREINC1, PRODH
	MOVFF	PREINC1, PRODL
	MOVF	PREINC1, W
	MOVFF	PREINC1, BSR
	MOVFF	PREINC1, STATUS
	RETFIE	

; ; Starting pCode block
S_timer__LCDDisplay	code
_LCDDisplay:
;	.line	31; timer.c	void LCDDisplay(char *text, BYTE pos)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x08, POSTDEC1
	MOVFF	r0x09, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
;	.line	33; timer.c	BYTE length = strlen(text);
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_strlen
	MOVWF	r0x04
	MOVFF	PRODL, r0x05
	MOVLW	0x03
	ADDWF	FSR1L, F
;	.line	34; timer.c	BYTE available = 32 - pos;
	MOVF	r0x03, W
	SUBLW	0x20
	MOVWF	r0x05
;	.line	35; timer.c	char *d = (char *)&LCDText[pos];
	CLRF	r0x06
	MOVLW	LOW(_LCDText)
	ADDWF	r0x03, F
	MOVLW	HIGH(_LCDText)
	ADDWFC	r0x06, F
	MOVF	r0x06, W
	MOVWF	r0x06
	MOVF	r0x03, W
	MOVWF	r0x03
	MOVLW	0x80
	MOVWF	r0x07
;	.line	37; timer.c	size_t n = (length < available) ? length : available;
	MOVF	r0x05, W
	SUBWF	r0x04, W
	BNC	_00111_DS_
	MOVFF	r0x05, r0x04
_00111_DS_:
	CLRF	r0x05
_00105_DS_:
;	.line	38; timer.c	while (n-- > 0) *d++ = *s++;
	MOVFF	r0x04, r0x08
	MOVFF	r0x05, r0x09
	MOVLW	0xff
	ADDWF	r0x04, F
	ADDWFC	r0x05, F
	MOVF	r0x08, W
	IORWF	r0x09, W
	BZ	_00107_DS_
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrget1
	MOVWF	r0x08
	INCF	r0x00, F
	BNC	_00120_DS_
	INFSNZ	r0x01, F
	INCF	r0x02, F
_00120_DS_:
	MOVFF	r0x08, POSTDEC1
	MOVFF	r0x03, FSR0L
	MOVFF	r0x06, PRODL
	MOVF	r0x07, W
	CALL	__gptrput1
	INCF	r0x03, F
	BNC	_00121_DS_
	INFSNZ	r0x06, F
	INCF	r0x07, F
_00121_DS_:
	BRA	_00105_DS_
_00107_DS_:
;	.line	39; timer.c	LCDUpdate();
	CALL	_LCDUpdate
	MOVFF	PREINC1, r0x09
	MOVFF	PREINC1, r0x08
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
__str_0:
	DB	0x45, 0x6c, 0x61, 0x70, 0x73, 0x65, 0x64, 0x20, 0x74, 0x69, 0x63, 0x6b
	DB	0x73, 0x3a, 0x20, 0x20, 0x25, 0x6c, 0x75, 0x20, 0x2b, 0x20, 0x25, 0x68
	DB	0x75, 0x00


; Statistics:
; code size:	  704 (0x02c0) bytes ( 0.54%)
;           	  352 (0x0160) words
; udata size:	   33 (0x0021) bytes ( 0.86%)
; access size:	   10 (0x000a) bytes


	end
