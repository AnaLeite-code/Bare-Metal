#include <avr/io.h>
#include <util/delay.h>

int main()
{
DDRB |= (1 << DDB4); // SAÍDA (LED)

while(1)
{
  PORTB ^= (1<<PORTB4);
  _delay_ms(1000);
}
  return 0;
}
