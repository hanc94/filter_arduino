#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

//Inicia señal PWM para frequencia de 15625 Hz
void initPWM(){
uint8_t sreg;

    TCCR1A=0xA2;
    TCCR1B=0x19;


    sreg=SREG;
    cli();
    ICR1=1024;
    SREG=sreg;

    sreg=SREG;
    cli();
    OCR1A=0;
    OCR1B=0;
    SREG=sreg;

    DDRB |= (1<<2) | (1<<1);
}

//Escribe ciclo util en el canal PWM (10 bits)
void myAnalogWrite(unsigned short v){
  uint8_t sreg;

    v=v&0x3ff;

    sreg=SREG;
    cli();
    OCR1A=v;
    SREG=sreg;
}


