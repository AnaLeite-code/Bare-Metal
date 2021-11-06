#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
  cli(); // Desativa todas as interrupções limpando a máscara de interrupção global.
  SREG |= (1 << 7);
  PCICR |= (1 << PCIE0); // Registrador que precisa ser habilitado.
  PCMSK0 |= (1 << PCINT0); // Registrador  do PCINTO.
  

  DDRB &= ~(1 << DDB0); // Configurar o pino PB0 como entrada, pois, quando colocar em 0V ( borda de descida) ele mudará o estado.
  PORTB |= (1 << PORTB0); 
  DDRB |= (1 << DDB5);

  sei(); // Habilita interrupções configurando a máscara de interrupção global.
  
  while(1)
  {
    PORTB ^= (1 << PORTB5);
    _delay_ms (3000);
  }
}

ISR(PCINT0_vect){
  PORTB ^= ( 1 << PORTB5);
} 
