#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
volatile int contador = 0;
int main(){
  cli();
  SREG |= (1 << 7);
  TCCR0A |= (1 << WGM01);
  TCCR0B |= (1 << CS01);
  TIMSK0 |= (1 << OCIE0A);
  OCR0A = 200;
  TCNT0 = 0;
  DDRB |= (1 << DDB5);
  sei();  
  while(1);
  return 0;
}
ISR(TIMER0_COMPA_vect)
{
  if(contador == 20000) 
  {
    PORTB ^= (1 << PORTB5);
    contador = 0;
  }
  else contador++;
}
