#ifndef MYSERIAL_H
#define MYSERIAL_H

#define FOSC 11059200
#define SCLK FOSC/384

char buff[50];
char *ser_b;
__sbit ser_c;

void start_serial(long int baud)
{
 long int ser_count;
 ES=0;
 TR1=0;
 SCON=SCON|0x50;
 TMOD=(TMOD&0x0F)|0x20;
 ser_count=256-(SCLK/baud);
 TH1=ser_count;
 TL1=ser_count;
 TR1=1;
 ES=1;
 EA=1;
}

void send_mess(char *ser_mess)
{
 ser_c=0;
 while(*ser_mess!=0x00)
 {
  SBUF=*ser_mess;
  *ser_mess++;
  while(ser_c==0)
  {
  }
  ser_c=0;
 }
}

void serial_interrupt() __interrupt(4)
{
 if(RI==1)
 {
  RI=0;
  if(SBUF==0X0D)
  {
   *ser_b=0x00;
   *ser_b++;
  }
  else if(SBUF==0X0A)
  {
   ser_c=1;
  }
  else
  {
   *ser_b=SBUF;
   *ser_b++;
  }
 }
 else
 {
  TI=0;
  ser_c=1;
 }
}

#endif