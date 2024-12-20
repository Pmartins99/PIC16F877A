/*
 * File:   newmain.c
 * Author: pablo
 *
 * Created on 19 de Dezembro de 2024, 18:12
 */


#include <xc.h>
#include <stdio.h>
#include "1cd.h"
#define _XTAL_FRE 8000000

// CONFIG
#pragma config FOSC = INTRC  // Oscilador interno, 8 MHz, sem saída de clock
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void main(void) {
    
    TRISA0 = 1;  // Botão entrada RA0
    TRISC0 = 0;  // Pino para controlar o motor como saída RC0
    TRISD = 0;    // LCD -> todos os pinos como saída RD0-RD5
    
    ANSEL = 0;  // Desativando entradas analógicas
    ANSELH = 0;
    
    // Início do LCD
    lcd_init();
    
    // Exibe a mensagem inicial
    lcd_clear(); 
    lcd_set_cursor(1, 1);
    lcd_write_string("Motor Desligado");

    while(1) {
        if (RA0 == 0) {  // Verifica se o botão foi pressionado
            LATC0 = 1;  // Liga o motor (RC0 = 1)
            lcd_clear();
            lcd_set_cursor(1, 1);
            lcd_write_string("Motor Ligado");
            __delay_ms(500);  // ajuda a evitar múltiplos acionamentos do botão
        } else {
            LATC0 = 0;  // Desliga o motor (RC0 = 0)
            lcd_clear();
            lcd_set_cursor(1, 1);
            lcd_write_string("Motor Desligado");
        }
    }

    return;
}