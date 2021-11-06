#include <stdio.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

volatile char letra = 'a' ; // Transmissão inicial.
volatile int contador = 0 ; // Inicialização.


int main(){
  
  cli(); // Desativa todas as interrupções.
  SREG |= ( 1 << 7 ) ; // Habilita a interrupção global.
  UBRR0H = 0 ;
  UBRR0L = 103 ; // Baud Rate (bps) de 9600.
 // UCSR0A |= ( 1 << TXC0 ) ;
/*             REGISTRADOR UCSR0A 
 *A flag TXC0 é setada quando todas as informações ou da-
 *dos já foram transmitidos e não há novos dados presen-
 *tes no buffer de transmissão (UDRn), ela é apagada auto-
 *maticamnete quando uma interrupção completa de transmis-
 *são é executada. 
*/
  UCSR0B  |=  ( 1 << TXEN0 ) | ( 1 << TXCIE0 );
/*             REGISTRADOR UCSR0B 
 *Uma interrupção completa de transmissão USART será gera-
 *da APENAS se o bit TXCIEn for gravado em um e a interrup-
 *ção global em SREG for gravado em um.
 *Gravar o bit TXENn em um habilita o transmissor USART. 
*/
  UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 ) ; 
/*             REGISTRADOR UCSR0C
 *Definiu o modo de operação do USART para Assíncrono, sem 
 *paridade, 1 stop bit e tamanho do caracter para 8 bit 
*/
  sei(); // Habilita todas as interrupções.

UDR0 = letra ; // Valor inicial de UDR0.
  
  while(1);
  return 0;
}

ISR(USART_TX_vect)
{
  letra ++ ; // Acrescenta um a variável letra.
  contador ++ ; // Acrescenta um a variável contador.
  
  if ( contador == 26 ) // Condição de parada.
  {
    UCSR0B = 0 ; // Reseta o registrador que define a interrupção.
  }
  
  UDR0 = letra ; // Informação é repassada para o buffer.
}

  
