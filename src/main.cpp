#define USB_SERIAL_ENABLED
#ifndef USB_SERIAL_ENABLED
#define TXD (PA_9)
#define RXD (PA_10)
#else
#define TXD (USBTX)
#define RXD (USBRX)
#endif

#include "mbed.h"

Serial seri(TXD,RXD);
DigitalOut led(LED1);

int main(void)
{
  char get_word=0b11111111;
  bool led_status=false;
  for(int i=0;i<3;i++)
  {
    while(seri.readable())seri.getc();
    wait(1);
  }
  seri.printf("\r\n Start Testing UART.\r\n");
  seri.printf(" ~ test ~ PleaseWord(orNumber) ...\r\n");
  while(1)
  {
    led_status=!led_status;
    led=led_status;
    if(seri.readable())
    {
      get_word=seri.getc();
      if(int(get_word) > 32)
      {
        seri.printf("\r\n\
        \r\n ---------------------------\
        \r\n |  I receve - %c (%i)- !  |\
        \r\n |     Thanks You.         |\
        \r\n ---------------------------\
        \r\n",get_word,int(get_word));
        if(get_word=='r') NVIC_SystemReset();
      }
    }
    wait(1);
  }
}
