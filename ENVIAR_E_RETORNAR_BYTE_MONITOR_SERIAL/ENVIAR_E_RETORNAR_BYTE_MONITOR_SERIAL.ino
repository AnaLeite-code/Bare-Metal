#define F_CPU 16000000UL
#define BAUD 9600

#include <stdio.h>
#include<avr/io.h>
#include<util/delay.h>
#include <util/setbaud.h>

unsigned char buf;

  void escritaEeprom(unsigned int endereco, unsigned char dado)
{
    while(EECR & (1<<EEPE));/* espera até que EEPE seja 0 */
    EEAR = endereco;/* passa o endereço na memória E2PROM */
    EEDR = dado;/* passa a informação contida na variável */
    EECR |= (1<<EEMPE);/* seta o registrador EEMPE para que a escrita seja possível em EEPE */
    EECR |= (1<<EEPE);/* escreve o dado na eeprom setando o registrador EEPE */
}
  unsigned char leituraEeprom(unsigned int endereco)
{
    while(EECR & (1<<EEPE));/* espera até que EEPE seja 0 */
    EEAR = endereco;/* passa o endereço na memória E2PROM */
    EECR |= (1<<EERE);/* começa a leitura da eeprom */
    return EEDR;/* retorna o dado que foi armazenado no registrador EEDR */
}
int main()
{
  cli();
    SREG |= (1 << 7);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0) ;/* aciona a recepção e transmissão da comunicação Serial */
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);/* comunicação assícrona, sem paridade, 1 stop bit e 8 bit */
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
  sei();
  while(1)
  {
    while (!(UCSR0A & (1<<RXC0)));/* espera todos os dados serem recebidos! */
    buf = UDR0;/* recebe o byte enviado pela serial! */
    _delay_ms(100);
    escritaEeprom(0x09,buf);/* escreve o dado no endereço da e2prom */
    _delay_ms(100);
    buf = leituraEeprom(0x06); /* lê e retorna o dado */
    _delay_ms(100);
  
    /*while(!(UCSR0A & (1 << UDRE0))); /* se UDRE0 for um, o buffer está vazio e, portanto,
    irá esvaziar a variável buf que estará pronta para ser usada novamente */
    UDR0 = buf;
  }
  return 0 ;
}
