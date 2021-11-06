#define F_CPU 16000000UL
#define BAUD 9600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/setbaud.h>

volatile char buf; // Variável que vai receber os dados de UDR0 e que depois será esvaziada.
int main(){
  cli(); // Desativa todas as interrupções.
  SREG |= (1 << 7); // Habilita a interrupção global.
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  /*RXEN0: Gravar este bit em um habilita o receptor USART.
   *TXEN0: Gravar este bit em um habilita o transmissor USART.
   *RXCIE0: Gravar este bit em um permite a interrupção na flag RXC0.
   */
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
  /*Definiu o modo de operação do USART para Assíncrono, sem paridade, 
   *1 stop bit e tamanho do caracter para 8 bit.
   */
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  /*Duas macros adicionais são fornecidas para os bytes baixo e alto do 
   *prescaler, respectivamente: UBRRL_VALUE é definido como o byte infe-
   *rior de UBRR_VALUE e UBRRH_VALUE é definido como o byte superior.
   *Todos os cálculos foram definidos em #include <util/setbaud.h>
   */
  sei(); // Habilita as interrupções.
  while(1);
  return 0;  
}
ISR(USART_RX_vect){
  while (!(UCSR0A & (1<<RXC0)));
  /*Essa flag é um quando há dados não lidos no buffer de recebiment(UDR0)
   *e limpo quando o UDR0 está vazio (ou seja, não contém dados não lidos.
   */
  buf = UDR0; // Variável Receptora recebe dado do buffer.
  while (!(UCSR0A & (1<<UDRE0)));
  /*A flag UDRE0 indica se o buffer de transmissão (UDR0) está pronto para 
   *receber novos dados. Se UDRE0 for um,o buffer está vazio e, portanto, 
   *pronto para ser gravado.
   */
  UDR0 = buf; // Buffer recebe dado da variável receptora.
}
