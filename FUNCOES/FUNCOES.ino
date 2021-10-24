#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define INPUT true
#define OUTPUT false

#define PORTAO_B 1
#define PORTAO_C 2
#define PORTAO_D 3


void newPinMode(int pino, bool modo, int portao);
void newDigitalWrite(int pino, bool valor, int portao);
bool newDigitalRead(int pino, int portao);



int main()
{
 newPinMode(DDB5,OUTPUT, PORTAO_B);
  
    while(1)
    {
      newDigitalWrite(PORTB5,HIGH,PORTAO_B);
    
      _delay_ms(1000); 
    
      newDigitalWrite(PORTB5,LOW,PORTAO_B);

      _delay_ms(1000); 
    
    }
  return 0;
}

/*
    Sintaxe: newPinMode()
    Descrição: Configura o pino especificado para funcionar como entrada ou saída.
    Parâmetros:
               -int pino: o numero do pino, que pode ser DDRXn.
               -bool modo: Este pode ser INPUT ou OUTPUT.
               -int porta: DDRB / DDRC / DDRD
*/
void newPinMode(int pino, bool modo, int portao)
{
  if (modo == INPUT)
  {
        if (portao == PORTAO_B)
        {
          DDRB &= ~(1 << pino);
        }
        
        else if (portao == PORTAO_C)
        {
          DDRC &= ~(1 << pino);
        }
        
        else if (portao == PORTAO_D)
        {
          DDRD &= ~(1 << pino);
        }
  }
  
  else if(modo == OUTPUT)
  {
    
        if (portao == PORTAO_B)
        {
          DDRB |= (1 << pino);
        }
        
        else if (portao == PORTAO_C)
        {
          DDRC |= (1 << pino);
        }
        
        else if (portao == PORTAO_D)
        {
          DDRD |= (1 << pino);
        }
    
  }
}
/*
    Sintaxe: newDigitalWrite()
    Descrição: Aciona um valor HIGH ou LOW em um pino digital.
    Parâmetros:
                   -int pino: o numero do pino, que pode ser PORTXn.
                   -bool valor: Este pode ser HIGH ou LOW.
                   -int porta0: PORTB / PORTC / PORTD
*/
void newDigitalWrite(int pino, bool valor, int portao)
{
            if (valor == HIGH)
            {
                  if (portao == PORTAO_B)
                  {
                    PORTB |= (1 << pino);
                  }
                  
                  else if (portao == PORTAO_C)
                  {
                    PORTC |= (1 << pino);
                  }
                  
                  else if (portao == PORTAO_D)
                  {
                    PORTD |= (1 << pino);
                  }
            }
            
            else if(valor == LOW)
            {
                  if (portao == PORTAO_B)
                  {
                    PORTB &= ~(1 << pino);
                  }
                  
                  else if (portao == PORTAO_C)
                  {
                    PORTC &= ~(1 << pino);
                  }
                  
                  else if (portao == PORTAO_D)
                  {
                    PORTD &= ~(1 << pino);
                  }
            }
 }


 /*
    Sintaxe: newDigitalRead()
    Descrição: Lê o valor de um pino digital especificado, que pode ser HIGH ou LOW.
    Parâmetros:
                   -int pino: o numero do pino, que pode ser PINXn.
                   -int portao: Este por sua vez pode ser PORTA0_B / PORTA0_C / PORTA0_D.
*/
bool newDigitalRead(int pino, int portao)
{

      if (portao == PORTAO_B)
      {
          if ((PINB & (1 << pino)) == (1 << pino))
          {
            return HIGH;
          }
          else 
          {
            return LOW;
          }
      }
      
      else if (portao == PORTAO_C)
      {
          if ((PINC & (1 << pino)) == (1 << pino))
          {
            return HIGH;
          }
          else 
          {
            return LOW;
          }
      }
      
      else if (portao == PORTAO_D)
      {
          if ((PIND & (1 << pino)) == (1 << pino))
          {
            return HIGH;
          }
          else 
          {
            return LOW;
          }
      }
}
