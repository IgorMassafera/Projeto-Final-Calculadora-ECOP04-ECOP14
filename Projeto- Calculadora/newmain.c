// Igor Massafera - 2020002338 - Projeto Calculadora

#include <pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "io.h"
#include "lcd.h"
#include "ssd.h"
#include "keypad.h"
#include "pwm.h"
#include "Calculator.h"

int operacao = -1;
int igual = 0;
int a1 = 0;

void updateCalc(){
    
    if(igual == 1 || a1 == 1){
        igual = 0;
        print(0);
    } // end if
    
} // end updateCalc

void main(){
    
    int cont=2, i, n, x=-1, y=-1, tempo, aux;
    char msg[16] = "Soma = *";
    volatile unsigned char a;
    
    ssdInit();
    kpInit();
    lcdInit();
    pwmInit();
    
    ADCON1=0x06;
    TRISB = 0b11111111;
    PORTB = 0b00000000;
    
    lcdPrint("Soma = RB3     ", 1);
    lcdPrint("Subtracao = RB4", 2);
    lcdPrint("Mult = RB5     ", 3);
    lcdPrint("Div = *      ", 4);
    
    for(;;){
        
       ADCON1 = 0x06;
       TRISB = 0b11111111;
       PORTB= 0b00000000;
       
       if(PORTBbits.RB3 == 0){
           operacao = 0;
        } // end if
              
        if(PORTBbits.RB4 == 0){ 
            operacao = 1;
        } // end if   
        
        if(PORTBbits.RB5 == 0){
            operacao = 2;
        } // end if
       
       ADCON1 = 0x00;
       TRISB = 0b00000000;
        
       if(kpRead() != aux){
            aux = kpRead();
           
            if(bitTst(kpRead(), 3)){ 
                
                updateCalc();
             
                ssdDigit(1, 0);
                
                if(cont % 2 == 0)
                    x = 1;
                
                else
                    y = 1;
                
                cont++;
            } // end if
            
            if(bitTst(kpRead(), 7)){
                
                updateCalc();
                
                ssdDigit(2, 0);
                
                if(cont % 2 == 0)
                    x = 2;
                
                else
                    y = 2;
                
                cont++;
            } // end if
            
            if(bitTst(kpRead(), 11)){
                
                updateCalc();
                
                ssdDigit(3, 0);
                
                if(cont % 2 == 0)
                    x = 3;
                
                else
                    y = 3;
                
                cont++;
            } // end if
            
            if(bitTst(kpRead(), 2)){
                
                updateCalc();
                
                ssdDigit(4, 0);
                
                if(cont % 2 == 0)
                    x = 4;
                
                else
                    y = 4;
                
                cont++;
            } // end if
            
            if(bitTst(kpRead(), 6)){
                
                updateCalc();
                
                ssdDigit(5, 0);
                
                if(cont % 2 == 0)
                    x = 5;
                
                else
                    y = 5;
                
                cont++;
            } // end if
            
            if(bitTst(kpRead(), 10)){
                
                updateCalc();
                
                ssdDigit(6, 0);
                
                if(cont % 2 == 0)
                    x = 6;
                
                else
                    y = 6;
                
                cont++;
            } // end if
            
            if(bitTst(kpRead(), 1)){
                
                updateCalc();
                
                ssdDigit(7, 0);
                
                if(cont % 2 == 0)
                    x = 7;
                
                else
                    y = 7;
                
                cont++;
            } // end if
            
            if(bitTst(kpRead(), 5)){
                
                updateCalc();
                
                ssdDigit(8, 0);
                
                if(cont % 2 == 0)
                    x = 8;
                
                else
                    y = 8;
                
                cont++;
            } // end if
            
            if(bitTst(kpRead(), 9)){
                
                updateCalc();
                
                ssdDigit(9, 0);
                
                if(cont % 2 == 0)
                    x = 9;
                
                else
                    y = 9;
                
                cont++;
            } // end if
            
            if(bitTst(kpRead(), 4)){
                
                updateCalc();
                
                ssdDigit(0, 0);
                
                if(cont % 2 == 0)
                    x = 0;
                
                else
                    y = 0;
                
                cont++;
            } // end if
              
            if(bitTst(kpRead(), 8))
                igual=1;
            
            if(bitTst(kpRead(), 0))
                operacao = 3;
            
       } // end if
       
       if(x != -1)
           reles(1);
       
       if(y != -1)
           reles(2);
      
       if(operacao == 0 && x != -1 && y != -1 && igual == 1){
                n = x + y;
                print(n);
                operacao = -1;
                x = -1;
                y = -1;   
        } // end if
       
       if(operacao == 1 && x != -1 && y != -1 && igual == 1){
                n = x - y;
                print(n);
                operacao = -1;
                x = -1;
                y = -1;      
        } // end if
       
       if(operacao == 2 && x != -1 && y != -1 && igual == 1){
                n = x * y;
                print(n);
                operacao = -1;
                x = -1;
                y = -1;      
        } // end if
       
       if(operacao == 3 && x != -1 && y != -1 && igual == 1){
                n = x / y;
                print(n);
                operacao = -1;
                x = -1;
                y = -1;      
        } // end if
   
       if(igual == 1){
           //ventoinha(0);
          // ventoinha(0);
          // ventoinha(0);
           ventoinha(1);
           ventoinha(0);
           reles(-1);
           igual = 0;
           a1 = 1;
           
       }
       
        for(tempo=0; tempo < 900; tempo++);
        ssdUpdate();
        kpDebounce();

    } // end for
        
} // end main