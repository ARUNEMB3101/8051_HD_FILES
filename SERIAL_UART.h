#ifndef SERIAL_UART_H
#define SERIAL_UART_H

#define FOSC 11059200
#define SCLK FOSC/384

void start_serial(long int);

char serial_buff[80];
char *serial_b;
char serial_n;
__bit serial_c,serial_k;
void get_rfid(void);
__bit rfid_verify(char*);

void main()
{
 serial_n=0x00;
 c=0;
 b=&buff[0];
 BUZ=0;
 start_serial(9600);
 servo_init();
 run_servo(R);
 delay(5);
 while(1)
 {
  while(c==0)
  {}
  c=0;
  rfid_verify(tag1);
  if(k==1)
  {
   run_servo(L);
   BUZ=1;
   delay(1);
   BUZ=0;
   delay(10);
   run_servo(R);
   REN=1;
   b=&buff[0];
  }
  else
  {
   run_servo(R);
   BUZ=1;
   delay(5);
   BUZ=0;
   REN=1;
   b=&buff[0];
  }
 }
}

void start_serial(long int baud)
{
 long int serial_count;
 ES=0;
 TR1=0;
 SCON=0x50;
 TMOD=(TMOD&0x0F)|0x20;
 serial_count=256-(SCLK/baud);
 TH1=serial_count;
 TL1=serial_count;
 TR1=1;
 ES=1;
 EA=1;
}

void serial_int() __interrupt(4)
{
 if(RI==1)
 {
  get_rfid();
 }
 
 else
 {
  TI=0;
 }
}


void get_rfid()
{
 RI=0;
 *b=SBUF;
 *b++;
 n++;
 if(n==12)
 {
  REN=0;
  b=&buff[0];
  c=1;
  n=0;
 }
 else
 {
 }
}

__bit rfid_verify(char tag[])
{
 int i;
 char v=0;
 for(i=0;i<12;i++)
 {
  if(tag[i]==buff[i])
  {
   v++;
  }
  else
  {
  }
 }
 if(v==12)
 {
  k=1;
 }
 else
 {
  k=0;
 }
 return k;
}
