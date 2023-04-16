#ifndef TIMERU_H
#define TIMERU_H

#define TIMERU_FOSC 11059200
#define TIMERU_TCLK TIMERU_FOSC/12
#define TIMERU_MS TIMERU_TCLK/200

int timeru_us;
int timeru_ms;
long int timeru_second;

void timer_10us(int);
void timer_5ms(int);
void timer_sec(char);
__sbit timeru_c,timeru_u,timeru_m,timeru_s;

void timer_10us(int timeru_t)
{
 timeru_c=0;
 timeru_u=1;
 timeru_m=0;
 timeru_s=0;
 timeru_us=timeru_t/10;
 ET0=0;
 TR0=0;
 TMOD=(TMOD&0xF0)|0x02;
 TL0=0xF7;
 TH0=0xF7;
 TR0=1;
 ET0=1;
 EA=1;
 while(timeru_c==0)
 {
 }
 timeru_c=0;
}

void timer_5ms(int timeru_t)
{
 timeru_c=0;
 timeru_u=0;
 timeru_m=1;
 timeru_s=0;
 timeru_ms=(timeru_t/5)*(TIMERU_MS/256);
 ET0=0;
 TR0=0;
 TMOD=(TMOD&0xF0)|0x02;
 TL0=0x00;
 TH0=0x00;
 TR0=1;
 ET0=1;
 EA=1;
 while(timeru_c==0)
 {
 }
 timeru_c=0;
}

void timer_sec(char timeru_t)
{
 timeru_c=0;
 timeru_u=0;
 timeru_m=0;
 timeru_s=1;
 timeru_second=timeru_t*(TIMERU_TCLK/256);
 ET0=0;
 TR0=0;
 TMOD=(TMOD&0xF0)|0x02;
 TL0=0x00;
 TH0=0x00;
 TR0=1;
 ET0=1;
 EA=1;
 while(timeru_c==0)
 {
 }
 timeru_c=0;
}

void timer() __interrupt(1)
{
 if(timeru_u==1)
 {
  if(timeru_us!=0)
  {
   timeru_us=timeru_us-1;
  }
  else
  {
   TR0=0;
   timeru_u=0;
   timeru_c=1;
  }
 }
 else if(timeru_m==1)
 {
  if(timeru_ms!=0)
  {
   timeru_ms=timeru_ms-1;
  }
  else
  {
   TR0=0;
   timeru_m=0;
   timeru_c=1;
  }
    
 }
 else if(timeru_s==1)
 {
  if(timeru_second!=0)
  {
   timeru_second=timeru_second-1;
  }
  else
  {
   TR0=0;
   timeru_s=0;
   timeru_c=1;
  }
 }
 else
 {
 }
}

#endif