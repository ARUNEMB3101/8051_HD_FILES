#ifndef RFID_H
#define RFID_H

#define RFID_FOSC 11059200
#define RFID_SCLK RFID_FOSC/384


char rfid_buff[13];
char *rfid_b;
char rfid_n;
__bit rfid_c,rfid_k;

void start_serial(long int);
void rfid_start(void);
void rfid_wait(void);
__bit rfid_verify(char*);
void get_rfid(void);

void start_serial(long int rfid_baud)
{
 long int rfid_count;
 ES=0;
 TR1=0;
 SCON=0x50;
 TMOD=(TMOD&0x0F)|0x20;
 rfid_count=256-(RFID_SCLK/rfid_baud);
 TH1=rfid_count;
 TL1=rfid_count;
 TR1=1;
 ES=1;
 EA=1;
}

void get_rfid()
{
 RI=0;
 *rfid_b=SBUF;
 *rfid_b++;
 rfid_n++;
 if(rfid_n==12)
 {
  *rfid_b=0x00;
  REN=0;
  rfid_b=&rfid_buff[0];
  rfid_c=1;
  rfid_n=0;
 }
 else
 {
 }
}

__bit rfid_verify(char tag[])
{
 int rfid_i;
 char rfid_v=0;
 for(rfid_i=0;rfid_i<12;rfid_i++)
 {
  if(tag[rfid_i]==rfid_buff[rfid_i])
  {
   rfid_v++;
  }
  else
  {
   break;
  }
 }
 if(rfid_v==12)
 {
  rfid_k=1;
 }
 else
 {
  rfid_k=0;
 }
 return rfid_k;
}

void rfid_wait()
{
 while(rfid_c==0)
 {
 }
 rfid_c=0;
 rfid_n=0;
 rfid_b=&rfid_buff[0];
}

void rfid_start()
{
 rfid_n=0;
 rfid_c=0;
 rfid_k=0;
 REN=1;
 rfid_b=&rfid_buff[0];
}

#endif