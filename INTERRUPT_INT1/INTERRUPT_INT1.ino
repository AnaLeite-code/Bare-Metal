#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
  cli(); // Desativa todas as interrupções limpando a máscara de interrupção global.
  EIMSK |= (1 << INT1);
  SREG |= (1 << 7); // 
  EICRA |= (1 << ISC11); // configura como borda de descida.

  DDRD &= ~(1 << DDD3); // Configurar o pino PD2 como entrada, pois, quando colocar em 0V ( borda de descida) ele mudará o estado.
  PORTD |= (1 << PORTD3);
  DDRB |= (1 << DDB5);

  sei(); // Habilita interrupções configurando a máscara de interrupção global.
  
  while:
//  {
//    PORTB ^= (1 << PORTB5);
//    _delay_ms (3000);
//  }
//}
  return 0;
ISR(INT1_vect){
  PORTB ^= ( 1 << PORTB5);//Muda o estado do led a cada interrupção
}
