#define F_CPU 16000000UL
#define BAUD 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/setbaud.h>

volatile char buf, i = 'i' ;

int main()
{
  cli();
  SREG |= (1 << 7);

  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  /*Duas macros adicionais são fornecidas para os bytes baixo e alto do 
  *prescaler, respectivamente: UBRRL_VALUE é definido como o byte 
  *inferior de UBRR_VALUE e UBRRH_VALUE é definido como o byte superior.
  *Todos os cálculos foram definidos em #include <util/setbaud.h>
  */
  
  while(!(UCSR0A & (1 << UDRIE0))); // Esperar o buffer ficar vazio
  UDR0 = i; // caracter "i"
  DDRB |= (1 << DDB5); // 
  sei();
  while(1);
  return 0;
}

ISR(USART_RX_vect){
  while(!(UCSR0A & (1 << RXC0))); // Esperar o dado ser recebido.
  buf = UDR0; // Valor da Serial

  if(buf == 't'){
    PORTB |= (1 << PORTB5); // Se for "t" liga o led
  }

  else 
  {
    PORTB &= ~(1 << PORTB5);
  }
  
  while(!(UCSR0A & (1 << UDRIE0)));
  UDR0 = buf;
}
