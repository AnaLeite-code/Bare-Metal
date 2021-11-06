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
int main(){
  
  cli();// Desativa todas as interrupções.
  
  TCCR1B |= (1 << CS11);// Prescale de 8
  TCNT1 = 0;//Habilita o registrador Timer.
  SREG |= (1 << 7);// Habilita a máscara de a interrupção glogal.
  TIMSK1 |= (1 << TOIE1);// Habilitando interrupção por overflow.
  
  sei();// Habilita todas as interrupções.

    
  DDRB |= (1 << DDB5);
  PORTB &= ~(1 << PB5);
  while(1);
  return 0;
}
ISR(TIMER1_OVF_vect)
{
  PORTB ^= (1 << PB5);
  TCNT1 =0;
  }
