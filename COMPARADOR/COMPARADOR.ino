#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/*
 * Timer de 16 bits: 0 a 2^16(65536)
 *    -Overflow
 *    -Comparador
 *    -PMW
 *    TCCR1B(CS12, CS11 e CS10)->Prescale
 */

int main()
{
  cli ();
  SREG |= (1 << 7); // interrupção global.
  TCCR1B |= ( 1 << CS12); // Prescale de 1024.
  TCCR1B |= ( 1 << CS10) | (1 << WGM12); 
  TCNT1 = 0; // Contador inicializado em 0.

  OCR1A = 31250;

/*  16M / 1024 = 15625 Hz -- 64 us
  64us x 65536 = 4,19 s

  65536 -- 4,19 s
    x   -- 2 s
    x = 31250
 */
  TIMSK1 |= ( 1 << OCIE1A); // Habilitando interrupção por Comparador.

  DDRB |= ( 1 << DDB5);
  PORTB &= ~(1 << PB5);
  sei ();

  
  
  while(1);
  return 0;
}
ISR(TIMER1_COMPA_vect)
{
  PORTB ^= ( 1 << PORTB5);
  TCNT1 = 0;
}
