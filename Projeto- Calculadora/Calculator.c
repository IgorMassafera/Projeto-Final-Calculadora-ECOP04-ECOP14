#include <pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "io.h"
#include "lcd.h"
#include "ssd.h"
#include "keypad.h"
#include "pwm.h"
#include "Calculator.h"

void print(int n){
    
    ssdDigit(n % 10, 3);
    ssdDigit((n/10) % 10, 2);
    ssdDigit((n/100) % 10, 1);
    ssdDigit((n/1000) % 10, 0);
    
} // end print

void reles(int rele){
    
    TRISCbits.TRISC0=0;
    TRISEbits.TRISE0=0;
    
    if(rele == 1){
        PORTCbits.RC0^=1;
        PORTEbits.RE0=0;
    } // end if
    
    if(rele == 2){
        PORTEbits.RE0^=1;
        PORTCbits.RC0=0;
    } // end if
    
    if(rele == -1){
        PORTCbits.RC0=0;
        PORTEbits.RE0=0;
    } // end if
    
} // end reles

void lcdPrint(char msg[16] ,int linha){
    
    unsigned char i;
    
    if(linha == 1){
        for(i=0; i < 16; i++)
            lcdData(msg[i]);
    } // end if
    
    if(linha == 2){
        lcdCommand(0xC0);
        
        for(i=0; i < 16; i++)
            lcdData(msg[i]);
    } // end if
    
    if(linha == 3){
        lcdCommand(0x90);
        
        for(i=0; i < 16; i++)
            lcdData(msg[i]);
    } // end if
    
    if(linha == 4){
        lcdCommand(0xD0);
        
        for(i=0; i < 16; i++)
            lcdData(msg[i]);
    } // end if
    
} // end lcdPrint

void ventoinha(int v){
    
    int i;
        
    if(v == 1)
        TRISCbits.RC2 = 1;
        
    else
        TRISCbits.RC2 = 0;
    
    for(i = 0; i < 30000; i++);    
    
} // end ventoinha

