#define F_CPU 16000000UL
#define BAUD 9600

#include <stdio.h>
#include<avr/io.h>
#include<util/delay.h>
#include <util/setbaud.h>

char j[] = "ACADEMIA STEM!\n";
char k[] = "SOFTWARE EMBARCADO!\n";

void send_array(char *string, int len){
  for(int i = 0; i < len; i++)
  {
    while(!(UCSR0A & (1<<UDRE0))); // 
    UDR0 = string[i];
  }
}

int main(){
  
  cli();
  SREG |= ( 1 << 7 ) ; // Aciona a interrupção global.
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  /*Duas macros adicionais são fornecidas para os bytes baixo e alto do 
  *prescaler, respectivamente: UBRRL_VALUE é definido como o byte 
  *inferior de UBRR_VALUE e UBRRH_VALUE é definido como o byte superior.
  *Todos os cálculos foram definidos em #include <util/setbaud.h>
  */
  UCSR0B  |=  ( 1 << TXEN0 ) ;
/*             REGISTRADOR UCSR0B 
 *Gravar o bit TXENn em um habilita o transmissor USART.
*/
  UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 ) ; 
/*             REGISTRADOR UCSR0C
 *Definiu o modo de operação do USART para Assíncrono, 
 *sem paridade, 1 stop bit e tamanho do caracter para 8 bit
 */
  sei();

  // UDR0 = sizeof(j); apenas uso quando o tamanho do vetor for especificado e.g. char j[4] = {'o','i','!','\n'};
  
  while(1){
  send_array(j,15);
  _delay_ms(500);
  send_array(k,20);
  _delay_ms(500);
}
  return 0;
}
